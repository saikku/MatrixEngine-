#ifndef WINDOW_H
#define WINDOW_H
#include "Object.h"

#include <EGL\eglplatform.h>


namespace Engine {
	class Application;
	class GraphicsSystem;
	
	class Window : public Object
	{
	public:

		Window();
		~Window();

		virtual EGLNativeWindowType getNativeWindow() const = 0;

		// Setget
		void setSize(int w, int h);
		int getWidth() const;
		int getHeight() const;

		void setApplication(Application* app);
		void setGraphics(GraphicsSystem* graphics);

		Application* getApplication() const;
		GraphicsSystem* getGraphics() const;

	private:
		int height;
		int width;

		Application*	m_app;
		GraphicsSystem*		m_graphics;


	};
}
#endif