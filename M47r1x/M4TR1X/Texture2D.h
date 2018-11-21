#ifndef _ENGINE_TEXTURE2D_H_
#define _ENGINE_TEXTURE2D_H_

#include "Object.h"

#include <GLES2\gl2.h>


namespace Engine
{
	// Texture2D-class
	class Texture2D :
		public Object
	{
	public:

		// Constructs and compiles new shader from given vertex and fragment shaders sources.
		Texture2D(int width, int height, int bytesPerPixel, const GLubyte* pixels);

		~Texture2D();

		// Binds shader
		GLuint getTextureId() const{return m_textureId;}
		
	private:
		// OpenGL Program object id
		GLuint m_textureId;
	};

}
#endif


