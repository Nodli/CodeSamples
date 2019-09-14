#include <windows.h>
#include <xinput.h>
#include <dsound.h>
#include <gl/gl.h>
#include <math.h>

#define PI 3.14159265359

constexpr unsigned char software_clear_color[4] = {0, 255, 255, 0}; // B, G, R, A
#define SOFTWARE_RENDERING 0
constexpr float opengl_clear_color[4] = {1.f, 0.f, 1.f, 0.f};
#define OPENGL_RENDERING 1
#define RENDERING SOFTWARE_RENDERING

// ---- Global Variables ---- //

static bool global_running = true;

static LPDIRECTSOUNDBUFFER global_audio_buffer;

#if RENDERING == SOFTWARE_RENDERING
struct win32_offscreen_buffer{
    BITMAPINFO info;
    void* memory;
    int width;
    int height;
};
static win32_offscreen_buffer global_backbuffer;
#endif

struct win32_sound_output{
    int channels;
    int samples_per_second;
    int bytes_per_sample;
    int buffer_seconds;
    int buffer_size;

    int wave_frequency;
    int samples_per_wave_period;
    short tone_volume;

    unsigned int running_audio_index;
};

static void win32_fill_sound_buffer(win32_sound_output& sound, DWORD write_offset, DWORD write_bytesize){
    VOID* first_region;
    DWORD first_region_size;
    VOID* second_region;
    DWORD second_region_size;

    if(SUCCEEDED(global_audio_buffer->Lock(
                    write_offset, write_bytesize,
                    &first_region, &first_region_size,
                    &second_region, &second_region_size,
                    0))){

        // TODO(hugo): Check which if condition is the best
        //if(((running_sample_index + isample) % samples_per_period) > (samples_per_period / 2)){
        //if(((running_sample_index + first_region_samples + isample) % samples_per_period) > (samples_per_period / 2)){

        // TODO(hugo): Check that first_region_size & second_region_size are valid ie even
        short* first_region_out = (short*)first_region;
        DWORD first_region_blocks = first_region_size / (sound.channels * sound.bytes_per_sample);
        for(DWORD iblock = 0; iblock < first_region_blocks; ++iblock){

            int t = (float)(sound.running_audio_index++) / (float)(sound.samples_per_wave_period) * 2.f * PI;
            short audio_sample = (short)(sinf(t) * sound.tone_volume);

            #if 0
            short audio_sample;
            if((running_audio_index++ / half_samples_per_wave_period) % 2){
                audio_sample = wave_high;
            }else{
                audio_sample = wave_low;
            }
            #endif

            *(first_region_out++) = audio_sample;
            *(first_region_out++) = audio_sample;
        }

        short* second_region_out = (short*)second_region;
        DWORD second_region_blocks = second_region_size / (sound.channels * sound.bytes_per_sample);
        for(DWORD iblock = 0; iblock < second_region_blocks; ++iblock){

            int t = (float)(sound.running_audio_index++) / (float)(sound.samples_per_wave_period) * 2.f * PI;
            short audio_sample = (short)(sinf(t) * sound.tone_volume);

#if 0
            short audio_sample;
            if((running_audio_index++ / half_samples_per_wave_period) % 2){
                audio_sample = wave_high;
            }else{
                audio_sample = wave_low;
            }
#endif

            *(second_region_out++) = audio_sample;
            *(second_region_out++) = audio_sample;
        }

        global_audio_buffer->Unlock(first_region, first_region_size, second_region, second_region_size);
    }

    }


    // ---- XInput Loading ---- //

    // NOTE(hugo): Support for XInputGetState
    typedef DWORD WINAPI xinput_get_state(DWORD dwUserIndex, XINPUT_STATE* pState);
    DWORD WINAPI XInputGetState_DUMMY(DWORD dwUserIndex, XINPUT_STATE* pState){return ERROR_DEVICE_NOT_CONNECTED;}
static xinput_get_state* XInputGetState_DYNAMIC = XInputGetState_DUMMY;
#define XInputGetState XInputGetState_DYNAMIC

// NOTE(hugo): Support for XInputSetState;
typedef DWORD WINAPI xinput_set_state(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration);
DWORD WINAPI XInputSetState_DUMMY(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration){return ERROR_DEVICE_NOT_CONNECTED;}
static xinput_set_state* XInputSetState_DYNAMIC = XInputSetState_DUMMY;
#define XInputSetState XInputSetState_DYNAMIC

static void win32_load_xinput(){

    HMODULE xinput_library = LoadLibraryA("xinput1_4.dll");
    if(!xinput_library){
        LoadLibraryA("xinput1_3.dll");
    }

    if(xinput_library){
        XInputGetState_DYNAMIC = (xinput_get_state*)GetProcAddress(xinput_library, "XInputGetState");
        XInputSetState_DYNAMIC = (xinput_set_state*)GetProcAddress(xinput_library, "XInputSetState");
    }else{
        // TODO(hugo): Diagnostic
    }
}

// ---- DirectSound Loading ---- //

// NOTE(hugo): Support for DirectSoundCreate;
typedef HRESULT WINAPI directsound_create(LPCGUID pcGUIdDevice, LPDIRECTSOUND* ppDS, LPUNKNOWN pUnkOuter);

// NOTE(hugo): Samples are the same as for DirectSound ie each channel has one sample per block
static void win32_init_directsound(HWND window, int samples_per_second, int buffer_size){

    // NOTE(hugo): Load the library
    HMODULE directsound_library = LoadLibraryA("dsound.dll");

    if(directsound_library){
        // NOTE(hugo): Get a DirectSound object
        directsound_create* DirectSoundCreate = (directsound_create*)GetProcAddress(directsound_library, "DirectSoundCreate");

        LPDIRECTSOUND directsound;
        if(DirectSoundCreate && SUCCEEDED(DirectSoundCreate(0, &directsound, 0))){
            if(SUCCEEDED(directsound->SetCooperativeLevel(window, DSSCL_PRIORITY))){

                // NOTE(hugo): The wave format is the same for the primary and secondary audio buffers
                WAVEFORMATEX wave_format = {};
                wave_format.wFormatTag = WAVE_FORMAT_PCM;
                wave_format.nChannels = 2;
                wave_format.nSamplesPerSec = samples_per_second;
                wave_format.wBitsPerSample = 16;
                wave_format.nBlockAlign = wave_format.nChannels * (wave_format.wBitsPerSample / 8);
                wave_format.nAvgBytesPerSec = samples_per_second * wave_format.nBlockAlign;

                // NOTE(hugo): Creating the primary buffer and checking that the wave format is supported
                DSBUFFERDESC buffer_description = {};
                buffer_description.dwSize = sizeof(buffer_description);
                buffer_description.dwFlags = DSBCAPS_PRIMARYBUFFER; // NOTE(hugo): DSBCAPS_GLOBALFOCUS

                LPDIRECTSOUNDBUFFER primary_buffer;
                if(SUCCEEDED(directsound->CreateSoundBuffer(&buffer_description, &primary_buffer, 0))){
                    OutputDebugStringA("primary_buffer create successfully\n");
                    if(SUCCEEDED(primary_buffer->SetFormat(&wave_format))){
                        OutputDebugStringA("primary_buffer format was set\n");

                    }else{
                        // TODO(hugo): Diagnostic
                    }
                }else{
                        // TODO(hugo): Diagnostic
                }

                // NOTE(hugo): Creating the secondary / audio buffer which is where audio data will be written
                // TODO(hugo): Check buffer_size against DSBSIZE_MIN and DSBSIZE_MAX (dsound.h)
                buffer_description.dwFlags = 0; // NOTE(hugo): DSBCAPS_GETCURRENTPOSITION2
                buffer_description.dwBufferBytes = buffer_size;
                buffer_description.lpwfxFormat = &wave_format;

                if(SUCCEEDED(directsound->CreateSoundBuffer(&buffer_description, &global_audio_buffer, 0))){
                        OutputDebugStringA("global_audio_buffer created successfully\n");

                }else{
                        // TODO(hugo): Diagnostic
                }

            }else{
                // TODO(hugo): Diagnostic
            }
        }else{
            // TODO(hugo): Diagnostic
        }
    }
}

// ---- Rendering ---- //

struct win32_window_dimension{
    int width;
    int height;
};
static win32_window_dimension win32_get_window_dimension(HWND window){
    win32_window_dimension result;

    RECT window_rect;
    GetClientRect(window, &window_rect);
    result.width = window_rect.right - window_rect.left;
    result.height = window_rect.bottom - window_rect.top;

    return result;
}

// ---- Software Rendering ---- //

#if RENDERING == SOFTWARE_RENDERING
static void render_clear(const win32_offscreen_buffer& buffer){
    // NOTE(hugo): Clearing the bitmap memory in ARGB format
    unsigned int* pixel_memory = (unsigned int*)buffer.memory;
    for(int ipix = 0; ipix != buffer.width * buffer.height; ++ipix){
        *(pixel_memory++) = (software_clear_color[0])
            | (software_clear_color[1] << 8)
            | (software_clear_color[2] << 16)
            | (software_clear_color[3] << 24); // B
    }
}

static void render_weird_gradient(const win32_offscreen_buffer& buffer, int blue_offset, int green_offset){
    // NOTE(hugo):
    // Windows is a Little Endian system ie lowest byte is the first byte and the highest byte is the last byte
    // Storage is top-Down and row-major
    unsigned int* pixel_memory = (unsigned int*) buffer.memory;
    for(int y = 0; y != buffer.height; ++y){
        for(int x = 0; x != buffer.width; ++x){
            *(pixel_memory++) = (unsigned char)(x + blue_offset) | ((unsigned char)(y + green_offset) << 8);
        }
    }
}

static void win32_resize_DIB_section(win32_offscreen_buffer& buffer, int width, int height){

    if(buffer.memory){
        VirtualFree(buffer.memory, 0, MEM_RELEASE);
    }

    buffer.width = width;
    buffer.height = height;

    constexpr int bitmap_bytes_per_pixel = 4;

    buffer.info.bmiHeader.biSize = sizeof(buffer.info);
    buffer.info.bmiHeader.biWidth = width;
    buffer.info.bmiHeader.biHeight = -height; // NOTE(hugo): Negative value makes the buffer top-down instead of bottom-up
    buffer.info.bmiHeader.biPlanes = 1;
    buffer.info.bmiHeader.biBitCount = bitmap_bytes_per_pixel * 8; // NOTE(hugo): 32 instead of 24 to get DWORD alignment ie faster access
    buffer.info.bmiHeader.biCompression = BI_RGB;

    const int bitmap_memory_size = width * height * bitmap_bytes_per_pixel;
    buffer.memory = VirtualAlloc(0, bitmap_memory_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE); // NOTE(hugo): Allocates at least a whole page

    //render_clear();
}

static void win32_display_buffer_in_window_software(win32_offscreen_buffer& buffer, HDC device_context, int window_width, int window_height){
    StretchDIBits(device_context,
            0, 0, window_width, window_height,
            0, 0, buffer.width, buffer.height,
            buffer.memory, &buffer.info,
            DIB_RGB_COLORS, SRCCOPY);
}

#endif

// ---- OpenGL Rendering ---- //

#if RENDERING == OPENGL_RENDERING
static void win32_init_opengl(HWND window){

    HDC device_context = GetDC(window);

    PIXELFORMATDESCRIPTOR desired_format = {};
    desired_format.nSize = sizeof(desired_format);
    desired_format.nVersion = 1;
    desired_format.dwFlags = PFD_SUPPORT_OPENGL | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    desired_format.iPixelType = PFD_TYPE_RGBA;
    desired_format.cColorBits = 32;
    desired_format.cDepthBits = 24;
    desired_format.cStencilBits = 8;
    desired_format.iLayerType = PFD_MAIN_PLANE;

    int suggested_format_index = ChoosePixelFormat(device_context, &desired_format);
    PIXELFORMATDESCRIPTOR suggested_format;
    DescribePixelFormat(device_context, suggested_format_index, sizeof(suggested_format), &suggested_format);

    SetPixelFormat(device_context, suggested_format_index, &suggested_format);

    HGLRC render_context = wglCreateContext(device_context);
    if(wglMakeCurrent(device_context, render_context)){

    }else{
        // TODO(hugo): Diagnostic
    }
    ReleaseDC(window, device_context);
}

static void win32_display_buffer_in_window_opengl(HDC device_context, int window_width, int window_height){
    glClearColor(opengl_clear_color[0], opengl_clear_color[1], opengl_clear_color[2], opengl_clear_color[3]);
    glClear(GL_COLOR_BUFFER_BIT);
    SwapBuffers(device_context);
    glViewport(0, 0, window_width, window_height);
}

#endif

// ---- Window Callback Function ---- //

LRESULT CALLBACK MainWindowCallback(HWND window,
        UINT message,
        WPARAM wparam,
        LPARAM lparam){

    LRESULT result = 0;

    switch(message){
        case WM_SIZE:
            OutputDebugStringA("WM_SIZE\n");
            {
#if RENDERING == SOFTWARE_RENDERING
                win32_window_dimension window_dimension = win32_get_window_dimension(window);
                win32_resize_DIB_section(global_backbuffer, window_dimension.width, window_dimension.height);
#endif
            }
            break;

        case WM_CLOSE:
            OutputDebugStringA("WM_CLOSE\n");
            {
                // TODO(hugo): Close the window
                global_running = false;
            }
            break;

        case WM_ACTIVATEAPP:
            OutputDebugStringA("WM_ACTIVATEAPP\n");
            {
            }
            break;

        case WM_DESTROY:
            OutputDebugStringA("WM_DESTROY\n");
            {
                // TODO(hugo): Recreate the window
                global_running = false;
            }
            break;

        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_KEYDOWN:
        case WM_KEYUP:
            //OutputDebugStringA("WM_SYSKEYDOWN or WM_SYSKEYUP or WM_KEYDOWN or WM_KEYUP\n");
            {
                int virtual_keycode = wparam;
                bool key_was_down = ((lparam >> 30) & 1) != 0;
                bool key_is_down = ((lparam >> 31) & 1) == 0;

                if(key_was_down != key_is_down){
                    if(virtual_keycode == 'W'){
                    }else if(virtual_keycode == 'A'){
                    }else if(virtual_keycode == 'S'){
                    }else if(virtual_keycode == 'D'){
                    }else if(virtual_keycode == 'Q'){
                    }else if(virtual_keycode == 'E'){
                    }else if(virtual_keycode == VK_UP){
                    }else if(virtual_keycode == VK_LEFT){
                    }else if(virtual_keycode == VK_RIGHT){
                    }else if(virtual_keycode == VK_ESCAPE){
                    }else if(virtual_keycode == VK_SPACE){

                        OutputDebugStringA("ESCAPE: ");
                        if(key_was_down){
                            OutputDebugStringA("key_was_down ");
                        }
                        if(key_is_down){
                            OutputDebugStringA("key_is_down ");
                        }
                        OutputDebugStringA("\n");
                    }
                }

                // NOTE(hugo): WM_SYSKEYUP and WM_SYSKEYDOWN are used for Alt + F4 so we need to reintroduce it
                int altkey_down = (lparam >> 29) & 1;
                if((virtual_keycode == VK_F4) && altkey_down){
                    global_running = false;
                }
            }
            break;

        case WM_PAINT:
            OutputDebugStringA("WM_PAINT\n");
            {
                win32_window_dimension window_dimension = win32_get_window_dimension(window);
                HDC device_context = GetDC(window);

                // NOTE(hugo): The BeginPaint and EndPaint instructions must always be called in response to WM_PAINT to be removed from the event queue
                PAINTSTRUCT paint;
                BeginPaint(window, &paint);

#if RENDERING == SOFTWARE_RENDERING
                render_clear(global_backbuffer);
                win32_display_buffer_in_window_software(global_backbuffer, device_context, window_dimension.width, window_dimension.height);
#elif RENDERING == OPENGL_RENDERING
                win32_display_buffer_in_window_opengl(device_context, window_dimension.width, window_dimension.height);
#endif

                EndPaint(window, &paint);

                ReleaseDC(window, device_context);
            }
            break;

        default:
            //OutputDebugStringA("default\n");
            {
                result = DefWindowProc(window, message, wparam, lparam);
            }
            break;
    }

    return result;
}

// ---- Windows Entry Point ---- //

int CALLBACK WinMain(HINSTANCE instance,
        HINSTANCE prev_instance,
        LPSTR command_line,
        int show_code){

    win32_load_xinput();

    WNDCLASSA window_class = {};
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = MainWindowCallback;
    window_class.hInstance = instance;
    window_class.lpszClassName = "ProjectWindowClass";

    LARGE_INTEGER count_frequency_result;
    QueryPerformanceFrequency(&count_frequency_result);
    long int count_frequency = count_frequency_result.QuadPart;

    if(RegisterClassA(&window_class)){
        HWND window = CreateWindowExA(
                0,
                window_class.lpszClassName,
                "Project",
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                0,
                0,
                instance,
                0);

        if(window){

            win32_sound_output sound;

            sound.channels = 2;
            sound.samples_per_second = 48000;
            sound.bytes_per_sample = sizeof(short);
            sound.buffer_seconds = 1;
            sound.buffer_size = sound.buffer_seconds
                * sound.samples_per_second
                * sound.channels
                * sound.bytes_per_sample;

            sound.wave_frequency = 440;
            sound.samples_per_wave_period = sound.samples_per_second / sound.wave_frequency;
            sound.tone_volume = 500;

            sound.running_audio_index = 0;

#if RENDERING == OPENGL_RENDERING
            win32_init_opengl(window);
#endif
            win32_init_directsound(
                    window,
                    sound.samples_per_second,
                    sound.buffer_size);
            if(FAILED(global_audio_buffer->Play(0, 0, DSBPLAY_LOOPING))){
                // TODO(hugo): Diagnostic
            }

            HDC device_context = GetDC(window);

            int xoffset = 0;
            int yoffset = 0;
            unsigned int running_audio_index = 0;

            global_running = true;

            LARGE_INTEGER last_counter;
            QueryPerformanceCounter(&last_counter);

            unsigned long int last_cycle_counter = __rdtsc();

            while(global_running){

                MSG message;

                // ---- Processing the window messages ---- //
                while(PeekMessage(&message, 0, 0, 0, PM_REMOVE)){
                    if(message.message == WM_QUIT){
                        global_running = false;
                    }

                    TranslateMessage(&message);
                    DispatchMessageA(&message);
                }

                // ---- Input ---- //
                // TODO(hugo): Determine the polling frequency
                // Using the XINPUTSTATE.dwPacketNumber increment

                // TODO(hugo): XInputGetState stalls when there is no controller plugged in
                // ie don't call it on unplugged controllers
                // use the plug in notifications + an array to see if a controller is plugged in

                DWORD result;
                for(DWORD icontroller = 0; icontroller < XUSER_MAX_COUNT; ++icontroller){
                    XINPUT_STATE controller_state;
                    if(XInputGetState(icontroller, &controller_state) == ERROR_SUCCESS){
                        // NOTE(hugo): Controller plugged in
                        const XINPUT_GAMEPAD& gamepad = controller_state.Gamepad;

                        bool dpad_up = (gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
                        bool dpad_down = (gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
                        bool dpad_left = (gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
                        bool dpad_right = (gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
                        bool left_shoulder = (gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
                        bool right_shoulder = (gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
                        bool buttonA = (gamepad.wButtons & XINPUT_GAMEPAD_A);
                        bool buttonB = (gamepad.wButtons & XINPUT_GAMEPAD_B);
                        bool buttonX = (gamepad.wButtons & XINPUT_GAMEPAD_X);
                        bool buttonY = (gamepad.wButtons & XINPUT_GAMEPAD_Y);

                        char left_trigger = gamepad.bLeftTrigger;
                        char right_trigger = gamepad.bRightTrigger;

                        short left_stick_X = gamepad.sThumbLX;
                        short left_stick_Y = gamepad.sThumbLY;
                        short right_stick_X = gamepad.sThumbRX;
                        short right_stick_Y = gamepad.sThumbRY;

                        if(buttonA){
                            ++yoffset;
                        }

                        if(buttonB){
                            XINPUT_VIBRATION vibration_state;
                            vibration_state.wLeftMotorSpeed = 65535;
                            vibration_state.wRightMotorSpeed = 0;
                            XInputSetState(icontroller, &vibration_state);
                        }

                        if(left_stick_X > - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
                                && left_stick_X < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){
                            left_stick_X = 0;
                        }
                        if(left_stick_Y > - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
                                && left_stick_Y < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){
                            left_stick_Y = 0;
                        }
                        if(right_stick_X > - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
                                && right_stick_X < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE){
                            right_stick_X = 0;
                        }
                        if(right_stick_Y > - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
                                && right_stick_Y < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE){
                            right_stick_Y = 0;
                        }

                        xoffset += (int)(10.f * left_stick_X / 32768.f);
                        yoffset += (int)(10.f * left_stick_Y / 32768.f);

                        sound.wave_frequency = 440 + (int)((left_stick_X / 32768.f) * 220.f);
                        sound.samples_per_wave_period = sound.samples_per_second / sound.wave_frequency;

                    }else{
                        // NOTE(hugo): XInput controller unavailable
                    }
                }

                // ---- Rendering ---- //

                win32_window_dimension window_dimension = win32_get_window_dimension(window);

#if RENDERING == SOFTWARE_RENDERING
                render_weird_gradient(global_backbuffer, xoffset, yoffset);
                win32_display_buffer_in_window_software(global_backbuffer, device_context, window_dimension.width, window_dimension.height);
#elif RENDERING == OPENGL_RENDERING
                win32_display_buffer_in_window_opengl(device_context, window_dimension.width, window_dimension.height);
#endif

                DWORD play_cursor;
                DWORD write_cursor;
                if(SUCCEEDED(global_audio_buffer->GetCurrentPosition(&play_cursor, &write_cursor))){

                    DWORD byte_to_lock = (sound.running_audio_index * sound.channels * sound.bytes_per_sample)
                        % sound.buffer_size;

                    // NOTE(hugo): Making sure the lock won't be inside the playing region
                    // Disabled becauses is causes audio dropouts when the play_cursor and running_audio_index overlap
                    #if 0
                    if(byte_to_lock >= play_cursor && byte_to_lock < write_cursor){
                        byte_to_lock = write_cursor;

                        int byte_offset = write_cursor - byte_to_lock;
                        running_audio_index += byte_offset / (audio_number_of_channels * audio_bytes_per_sample);
                    }
                    #endif

                    DWORD write_offset = byte_to_lock;
                    DWORD write_bytesize;

                    if(byte_to_lock > play_cursor){
                        write_bytesize = (sound.buffer_size - byte_to_lock) + play_cursor;
                    }else{
                        write_bytesize = play_cursor - byte_to_lock;
                    }

                    win32_fill_sound_buffer(sound, write_offset, write_bytesize);

                    LARGE_INTEGER end_counter;
                    QueryPerformanceCounter(&end_counter);

                    unsigned long int end_cycle_counter = __rdtsc();
                    int elapsed_cycle_counter = (int)((end_cycle_counter - last_cycle_counter) / 1000000);

                    long int elapsed_counter = end_counter.QuadPart - last_counter.QuadPart;
                    int frame_milliseconds = (int)((1000 * elapsed_counter) / count_frequency);
                    int frames_per_second = (int)(count_frequency / elapsed_counter);

                    char print_buffer[256];
                    wsprintfA(print_buffer, "ms / frame: %i\nframes per second: %i\nmegacycles elapsed: %i\n", frame_milliseconds, frames_per_second, elapsed_cycle_counter);
                    OutputDebugStringA(print_buffer);

                    last_counter = end_counter;
                    last_cycle_counter = end_cycle_counter;
                }
            }

            ReleaseDC(window, device_context);

        }else{
            // TODO(hugo): Diagnostic
        }

    }else{
        // TODO(hugo): Diagnostic
    }

    return 0;
}
