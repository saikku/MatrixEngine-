#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H
#include "Object.h"
#include "ResourceManager.h"

namespace Engine{
	class Shader;
	class Texture2D;

	class Window;
	class GraphicsSystem : public Object

	{
	public:

		virtual void drawObject(Shader* shader, float* textureCoords, float vertices[], int numvertices) = 0;
		// Clears the screen using given color
		virtual void clearScreen(float red, float green, float blue) = 0;

		// Draws vertices as triangles using given shader.
		virtual void drawTriangles(Shader* shader, float vertices[], int numvertices) = 0;

		// Draws vertices and texture coordinates as triangles using given shader.
		virtual void drawTriangles(Shader* shader, float vertices[], float textureCoords[], int numvertices) = 0;

		// Draws vertices and texture coordinates as triangles using given shader. Setys also texture sampler.
		virtual void drawTriangles(Shader* shader, Texture2D* texture, float vertices[], float textureCoords[], int numvertices) = 0;

		// Method for swapping backbuffer to screen.
		virtual void swapBuffers() = 0;

		virtual void drawBitmapText(char *string, float x, float y, float z, float r, float g, float b) = 0;

		GraphicsSystem();
		~GraphicsSystem();
	};
}

#endif
