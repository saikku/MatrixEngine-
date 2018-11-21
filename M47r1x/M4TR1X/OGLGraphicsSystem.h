#ifndef OGLGRAPHICSSYSTEM_H
#define OGLGRAPHICSSYSTEM_H
#include "Ref.h"
#include "GraphicsSystem.h"
#include <GLES2\gl2.h>
#include <EGL\egl.h>
#include "ResourceManager.h"

namespace Engine{
	class Window;
	
	class OGLGraphicsSystem : public GraphicsSystem
	{
	public:
		// Creates new OpenGL ES 2.0 Graphics System binded to given window.
		OGLGraphicsSystem(Window* window);
		~OGLGraphicsSystem();

		virtual void drawObject(Shader* shader, float* textureCoords, float vertices[], int numvertices);

		virtual void clearScreen(float red, float green, float blue);

		virtual void drawTriangles(Shader* shader, float vertices[], int numvertices);

		virtual void drawTriangles(Shader* shader, float vertices[], float textureCoords[], int numvertices);

		virtual void drawTriangles(Shader* shader, Texture2D* texture, float vertices[], float textureCoords[], int numvertices);
	
		virtual void swapBuffers();	
	
		virtual void drawBitmapText(char *string, float x, float y, float z, float r, float g, float b);

	private:
		Engine::Ref<Window> m_window;	// Window where graphics is binded
		bool isActive;					// True-flag if all is okay.
		Resource::ResourceManager* resMngr = new Resource::ResourceManager;

		// Embedded OpenGLES member variables
		EGLDisplay m_eglDisplay; // Display object
		EGLContext m_eglContext; // Context object
		EGLSurface m_eglSurface; // Surface object



	};
}
#endif