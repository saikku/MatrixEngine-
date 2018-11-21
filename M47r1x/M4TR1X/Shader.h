#ifndef SHADER_H
#define SHADER_H
#include "Object.h"
#include <GLES2\gl2.h>

namespace Engine{
	class Shader : public Object
	{
	public:

		Shader(const char* const vShaderStr, const char* const fShaderStr);

		~Shader();

		// Binds shader
		void useShader();

		// Retruns OpenGL id of shader uniform by name.
		GLuint getUniformLocation(const char* const uniformName);

	private:
		// OpenGL Program object id
		GLuint m_programObject;

		GLuint loadShader(GLenum type, const char *shaderSrc);
	};
}

#endif