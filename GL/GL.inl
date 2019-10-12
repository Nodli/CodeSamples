#include "print.h"

namespace gl{

    //#ifndef _WIN32
    inline void privateProgramAttachShader(Handle program){};
    //#endif

    template<typename... ShaderHandle>
        void privateProgramAttachShader(Handle program, Handle shader, ShaderHandle&... other){
            glAttachShader(program, shader);
            privateProgramAttachShader(program, other...);
        }

    template<typename... ShaderHandle>
        void LoadProgram(Handle handle, ShaderHandle&... shader){
            privateProgramAttachShader(handle, shader...);
            glLinkProgram(handle);
            LogProgramError(handle, "CreateProgram");
        }

    template<typename... ShaderHandle>
        Handle CreateProgram(ShaderHandle&... shader){
            Handle output = glCreateProgram();
            LoadProgram(output, shader...);

            return output;
        }
}
