#include "Shader.h"
#include <GLES2\gl2.h>
#include <malloc.h>
#include <stdio.h>

namespace Engine
{

	Shader::Shader(const char* const vShaderStr, const char* const fShaderStr)
		: Object()
		, m_programObject(0)
	{
		// Load the vertex/fragment shaders
		GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vShaderStr);
		GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fShaderStr);

		// Create the program object
		m_programObject = glCreateProgram();
		if (m_programObject == 0)
		{
			printf("Error while creating shader program object\n");
		}

		glAttachShader(m_programObject, vertexShader);
		glAttachShader(m_programObject, fragmentShader);

		// Bind vPosition to attribute 0   
		glBindAttribLocation(m_programObject, 0, "vPosition");

		// Link the program
		glLinkProgram(m_programObject);

		// Check the link status
		GLint linked;
		glGetProgramiv(m_programObject, GL_LINK_STATUS, &linked);

		if (!linked)
		{
			GLint infoLen = 0;
			glGetProgramiv(m_programObject, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen > 1)
			{
				char* infoLog = (char*)malloc(sizeof(char) * infoLen);
				glGetProgramInfoLog(m_programObject, infoLen, NULL, infoLog);
				printf("Error linking program:\n%s\n", infoLog);
				free(infoLog);
			}

			glDeleteProgram(m_programObject);
			return;
		}
	}


	Shader::~Shader()
	{
	}


	void Shader::useShader()
	{
		// Use the program object
		glUseProgram(m_programObject);
	}

	GLuint Shader::getUniformLocation(const char* const uniformName)
	{
		return glGetUniformLocation(m_programObject, uniformName);
	}

	GLuint Shader::loadShader(GLenum type, const char *shaderSrc)
	{
		GLuint shader;
		GLint compiled;


		// Create the shader object
		shader = glCreateShader(type);

		if (shader == 0){
		return 0;
	}
		//// Load the shader source
		glShaderSource(shader, 1, &shaderSrc, 0);

		//// Compile the shader
		glCompileShader(shader);

		//// Check the compile status
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen > 1)
			{
				char* infoLog = (char*)malloc(sizeof(char) * infoLen);
				glGetShaderInfoLog(shader, infoLen, 0, infoLog);
				printf("Error compiling shader:\n%s\n", infoLog);
				free(infoLog);
			}

			glDeleteShader(shader);
			return -1;
		}

		return shader;
		return 1;

	}

}