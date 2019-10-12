#pragma once

#include "gl3w.h"

namespace gl{

    // NOTE(hugo): typedef does not make a strong typing requirement ie a Shader is automatically cast to any GLuint typedef
    typedef GLuint Handle;
    typedef Handle Shader;
    typedef Handle Program;
    typedef Handle Texture;
    typedef Handle Framebuffer;
    typedef Handle Buffer;
    typedef Handle VertexArray;

    void LoadShader(Shader handle,
            const char* const shader_code,
            const GLint shader_length = -1);
    Shader CreateShader(const GLenum shader_type,
            const char* const shader_code,
            const GLint shader_length = -1);
    inline void DeleteShader(Shader handle){glDeleteShader(handle);};

    template<typename... ShaderHandle>
    void LoadProgram(Program handle, ShaderHandle&... shader);
    template<typename... ShaderHandle>
    Program CreateProgram(ShaderHandle&... shader);
    inline void DeleteProgram(Program handle){glDeleteProgram(handle);};

    struct ProgramBinary{
        GLsizei length;
        GLenum format;
        char* memory;
    };
    ProgramBinary CacheProgram(Program handle);
    Program CreateProgramFromCache(ProgramBinary cache);

    inline Texture CreateTexture(){Texture output; glGenTextures(1, &output); return output;};
    inline void Delete(Texture handle){glDeleteTextures(1, &handle);};

    inline Framebuffer CreateFramebuffer(){Framebuffer output; glGenFramebuffers(1, &output); return output;};
    inline void DeleteFramebuffer(Handle handle){glDeleteFramebuffers(1, &handle);};

    inline Buffer CreateBuffer(){Buffer output; glGenBuffers(1, &output); return output;};
    inline void DeleteBuffer(Buffer handle){glDeleteBuffers(1, &handle);};

    inline VertexArray CreateVertexArray(){VertexArray output; glGenVertexArrays(1, &output); return output;};
    inline void DeleteVertexArray(VertexArray handle){glDeleteVertexArrays(1, &handle);};

    // ---- Error Detection ---- //

    void LogReadableError(const GLenum error_code);
	void LogReadableFramebufferError(const GLenum error_code);

	bool LogError(const char* const log_label = nullptr);
	bool LogShaderError(const GLuint shader, const char* log_label = nullptr);
	bool LogProgramError(const GLuint program, const char* log_label = nullptr);
	bool LogFramebufferError(const GLenum target, const char* log_label = nullptr);
	bool LogNamedFramebufferError(const GLint framebuffer, const char* log_label = nullptr);

    // ---- Error Message Callback ---- //

    void LogDebugSourceMessage(const GLenum source_code);
    void LogDebugTypeMessage(const GLenum type_code);
    void LogDebugSeverityMessage(const GLenum severity_code);
    void DebugMessageCallback(GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* userParam);
    void SetupDebugCallback();
}

#include "GL.inl"
