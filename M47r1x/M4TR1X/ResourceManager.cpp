#include "ResourceManager.h"

namespace Resource{
	int ResourceManager::loadResource(const char * filename, int width, int height){
		unsigned char * data;
		FILE * file;
		file = fopen(filename, "rb");
		/*
		if (file == NULL){

		// ei löydy tai muu virhe
		std::cout << "Error loading file " << filename << "." << std::endl;
		return false;
		}
		data = (unsigned char *)malloc(width * height * 3);
		fread(data, width*height * 3, 1, file);
		fclose(file);

		glEnable(GL_TEXTURE_2D);
		glNormal3f(0, 0, 1);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(0.0, 0.0);
		glTexCoord2f(0.0, 1.0); glVertex2f(0.0, 1.0);
		glTexCoord2f(1.0, 1.0); glVertex2f(1.0, 1.0);
		glTexCoord2f(1.0, 0.0); glVertex2f(1.0, 0.0);
		glEnd();
		glFlush();
		glDisable(GL_TEXTURE_2D);


		// TEXTURE EI SAA MISSÄÄN MITÄÄN ARVOA?
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		free(data);

		*/
		// SOIL lataa kuvan
		texture = SOIL_load_OGL_texture(
			filename,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);


		resVector.insert(std::make_pair(filename, texture));
		return texture;
	}

	ResourceManager::ResourceManager()
	{
	}


	ResourceManager::~ResourceManager()
	{
	
	}

	int ResourceManager::getID(const char * name){

		std::map< std::string, int>::iterator it = resVector.find(name);
		if (it == resVector.end())
		{
			// ei löydy, ladataan uudestaan
			texture = loadResource(name, 32, 32);

			resVector.insert(std::make_pair(name, texture));
			it = resVector.find(name);
			assert(it != resVector.end());
			std::cout << it->second;

			return it->second;
		}
		std::cout << it->second;
		return it->second;
	}
}