#include "Texture2D.h"
#include <GLES2\gl2.h>
#include <malloc.h>
#include <stdio.h>

namespace Engine
{
	Texture2D::Texture2D(int width, int height, int bytesPerPixel, const GLubyte* pixels)
		: Object()
		, m_textureId(0)
	{
		// Use tightly packed data
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Generate a texture object
		glGenTextures(1, &m_textureId);

		// Bind the texture object
		glBindTexture(GL_TEXTURE_2D, m_textureId);

		// Load the texture
		GLuint fmt = bytesPerPixel == 3 ? GL_RGB : GL_RGBA; // Format is either RGB or RGBA depending on bit depth
		glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, width, 0, fmt, GL_UNSIGNED_BYTE, pixels);

		// Set the filtering mode
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}


	Texture2D::~Texture2D()
	{
	}

}