#include "GL.h"
#include <cassert>

namespace gl{
    void LoadShader(Handle handle,
            const char* const code,
            const GLint length){

        assert(handle != 0);

        glShaderSource(handle, 1, (const GLchar**) &code, (const GLint*) &length);
        glCompileShader(handle);
        LogShaderError(handle, "CreateShader");
    }

    Handle CreateShader(
            const GLenum type,
            const char* const code,
            const GLint length){

        Handle output = glCreateShader(type);
        LoadShader(output, code, length);

        return output;
    }

    ProgramBinary CacheProgram(Program handle){
        GLint link_status;
        glGetProgramiv(handle, GL_LINK_STATUS, &link_status);

        assert(handle != 0 && link_status == GL_TRUE);

        ProgramBinary cache;

        GLint binary_length;
        glGetProgramiv(handle, GL_PROGRAM_BINARY_LENGTH, &binary_length);
        cache.memory = new char[binary_length];
        glGetProgramBinary(handle, binary_length, &cache.length, &cache.format, cache.memory);

        return cache;
    }

    Program CreateProgramFromCache(ProgramBinary cache){
        Program output = glCreateProgram();
        glProgramBinary(output, cache.format, cache.memory, cache.length);

        return output;
    }

    void LogReadableError(const GLenum error_code){
        switch(error_code){
            case GL_INVALID_ENUM:
                LOG("GL_INVALID_ENUM",
                        "An unacceptable value is specified for an enumerated argument");
                break;

            case GL_INVALID_VALUE:
                LOG("GL_INVALID_VALUE",
                        "A numeric argument is out of range");
                break;

            case GL_INVALID_OPERATION:
                LOG("GL_INVALID_OPERATION",
                        "The specified operation is not allowed in the current state");
                break;

            case GL_STACK_OVERFLOW:
                LOG("GL_STACK_OVERFLOW",
                        "An attempt has been made to perform an operation that would cause an internal stack to overflow");
                break;

            case GL_STACK_UNDERFLOW:
                LOG("GL_STACK_UNDERFLOW",
                        "An attempt has been made to perform an operation that would cause an internal stack to underflow");
                break;

            case GL_OUT_OF_MEMORY:
                LOG("GL_OUT_OF_MEMORY",
                        "There is not enough memory left to execute the command");
                break;

            case GL_INVALID_FRAMEBUFFER_OPERATION:
                LOG("GL_INVALID_FRAMEBUFFER_OPERATION",
                        "The framebuffer object is not complete");
                break;

            case GL_CONTEXT_LOST:
                LOG("GL_CONTEXT_LOST",
                        "The OpenGL context has been lost, due to a graphics card reset");
                break;
        }
    }

    void LogReadableFramebufferError(const GLenum error_code){
        switch(error_code){
            case GL_FRAMEBUFFER_UNDEFINED:
                LOG("GL_FRAMEBUFFER_UNDEFINED",
                        "is returned if the specified framebuffer is the default read or draw framebuffer, but the default framebuffer does not exist");
                break;

            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                LOG("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT",
                        "is returned if any of the framebuffer attachment points are framebuffer incomplete");
                break;

            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                LOG("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT",
                        "is returned if the framebuffer does not have at least one image attached to it");
                break;

            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                LOG("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER",
                        "is returned if the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAW_BUFFERi");
                break;

            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                LOG("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER",
                        "is returned if the value of GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER");
                break;

            case GL_FRAMEBUFFER_UNSUPPORTED:
                LOG("GL_FRAMEBUFFER_UNSUPPORTED",
                        "is returned if the combination of internal formats of the attaches images violates an implementation-dependant set of restrictions");
                break;

            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
                LOG("GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE",
                        "is returned if the value of GL_RENDER_BUFFER_SAMPLES is not the same for all attached renderbuffers; if the value of GL_TEXTURE_SAMPLES is not the same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES\n",
                        "is also returned if the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of GL_TEXTURE_FIXED_LOCATIONS is not GL_TRUE for all attached textures2: The value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of GL_TEXTURE_FIXED_LOCATIONS is not GL_TRUE for all attached textures");
                break;

            case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
                LOG("GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS",
                        "is returned if any framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target");
                break;
        }
    }


    bool LogError(const char* log_label){
        GLenum error_status = GL_NO_ERROR;
        bool any_error = false;

        while((error_status = glGetError()) != GL_NO_ERROR){
            any_error = true;
            LOG(log_label, "OpenGL Error with code", error_status);
            LogReadableError(error_status);
        }

        return any_error;
    }

    bool LogShaderError(const GLuint shader, const char* log_label){
        GLint shader_status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_status);

        if(!shader_status){
            int shader_log_length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &shader_log_length);

            char* shader_log = new char[shader_log_length];
            glGetShaderInfoLog(shader, shader_log_length, NULL, shader_log);
            LOG(log_label, "OpenGL Error in shader", shader);
            RAWLOG(shader_log);
            delete[] shader_log;

            return false;
        }

        return true;
    }

    bool LogProgramError(const GLuint program, const char* log_label){
        GLint linking_status;
        glGetProgramiv(program, GL_LINK_STATUS, &linking_status);

        if(!linking_status){
            int program_log_length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &program_log_length);

            char* program_log = new char[program_log_length];
            glGetProgramInfoLog(program, program_log_length, NULL, program_log);
            LOG(log_label, "OpenGL Error with program", program);
            RAWLOG(program_log);
            delete[] program_log;

            return false;
        }

        return true;
    }

    bool LogFramebufferError(const GLenum target, const char* log_label){
        GLenum framebuffer_status = glCheckFramebufferStatus(target);

        if(framebuffer_status != GL_FRAMEBUFFER_COMPLETE){
            LOG(log_label, "OpenGL Error : framebuffer", target, "is incomplete");
            LogReadableFramebufferError(framebuffer_status);

            return false;
        }

        return true;
    }

    bool LogNamedFramebufferError(const GLint framebuffer, const char* log_label){
        GLenum framebuffer_status = glCheckNamedFramebufferStatus(framebuffer, GL_FRAMEBUFFER);

        if(framebuffer_status != GL_FRAMEBUFFER_COMPLETE){
            if(framebuffer){
                LOG(log_label, "OpenGL Error : framebuffer", framebuffer, "is incomplete");
            }else{
                LOG(log_label, "OpenGL Error : fallback target GL_FRAMEBUFFER is incomplete");
            }
            LogReadableFramebufferError(framebuffer_status);

            return false;
        }

        return true;
    }

    void LogDebugSourceMessage(const GLenum source_code){
        switch(source_code){
            case GL_DEBUG_SOURCE_API:
                LOG("GL_DEBUG_SOURCE_API",
                        "Generated by calls to the OpenGL API");
                break;

            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                LOG("GL_DEBUG_SOURCE_WINDOW_SYSTEM",
                        "Generated by calls to a window-system API");
                break;

            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                LOG("GL_DEBUG_SOURCE_SHADER_COMPILER",
                        "Generated by a compiler for a shading language");
                break;

            case GL_DEBUG_SOURCE_THIRD_PARTY:
                LOG("GL_DEBUG_SOURCE_THIRD_PARTY",
                        "Generated by an application associated with OpenGL");
                break;

            case GL_DEBUG_SOURCE_APPLICATION:
                LOG("GL_DEBUG_SOURCE_APPLICATION",
                        "Generated by the user of this application");
                break;

            case GL_DEBUG_SOURCE_OTHER:
                LOG("GL_DEBUG_SOURCE_OTHER",
                        "Generated by some unknown source");
                break;

        }
    }

    void LogDebugTypeMessage(const GLenum type_code){
        switch(type_code){
            case GL_DEBUG_TYPE_ERROR:
                LOG("GL_DEBUG_TYPE_ERROR",
                        "An error, typically from the API");
                break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                LOG("GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR",
                        "Some behavior marked deprecated has been used");
                break;

            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                LOG("GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR",
                        "Something has invoked undefined behavior");
                break;

            case GL_DEBUG_TYPE_PORTABILITY:
                LOG("GL_DEBUG_TYPE_PORTABILITY",
                        "Some functionality the user relies upon is not portable");
                break;

            case GL_DEBUG_TYPE_PERFORMANCE:
                LOG("GL_DEBUG_TYPE_PERFORMANCE",
                        "Code has triggered possible performance issues");
                break;

            case GL_DEBUG_TYPE_MARKER:
                LOG("GL_DEBUG_TYPE_MARKER",
                        "Command stream annotation");
                break;

            case GL_DEBUG_TYPE_PUSH_GROUP:
                LOG("GL_DEBUG_TYPE_PUSH_GROUP",
                        "Group pushing");
                break;

            case GL_DEBUG_TYPE_POP_GROUP:
                LOG("GL_DEBUG_TYPE_POP_GROUP",
                        "Group poping");
                break;

            case GL_DEBUG_TYPE_OTHER:
                LOG("GL_DEBUG_TYPE_OTHER",
                        "Unknown type");
                break;
        }
    }

    void LogDebugSeverityMessage(const GLenum severity_code){
        switch(severity_code){
            case GL_DEBUG_SEVERITY_HIGH:
                LOG("GL_DEBUG_SEVERITY_HIGH",
                        "All OpenGL Errors, shader compilation / linking errors, or highly-dangerous undefined behavior");
                break;

            case GL_DEBUG_SEVERITY_MEDIUM:
                LOG("GL_DEBUG_SEVERITY_MEDIUM",
                        "Major performance warnings, shader compilation / linking warnings, or the use of deprecated functionality");
                break;

            case GL_DEBUG_SEVERITY_LOW:
                LOG("GL_DEBUG_SEVERITY_LOW",
                        "Redundant state change performance warning, or unimportant undefined behavior");
                break;

            case GL_DEBUG_SEVERITY_NOTIFICATION:
                LOG("GL_DEBUG_SEVERITY_NOTIFICATION",
                        "Anything that isn't an error or performance issue");
                break;
        }
    }

    void DebugMessageCallback(GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* userParam){

        LogDebugSourceMessage(source);
        LogDebugTypeMessage(type);
        LogDebugSeverityMessage(severity);
        LOG("GL CALLBACK for ID :", id, (type == GL_DEBUG_TYPE_ERROR ? "which is a GL_ERROR" : ""), '\n', "MESSAGE", message);
        LogError();
    }

    void SetupDebugCallback(){
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        //glDebugMessageCallback(DebugMessageCallback, 0);
    }
}
