#include "Window.h"

namespace Engine
{

	Window::Window()
		: Object()
		, m_app(0)
		, m_graphics(0)
	{
	}


	Window::~Window()
	{
	}


	int Window::getWidth() const
	{
		return width;
	}


	int Window::getHeight() const
	{
		return height;
	}


	void Window::setSize(int w, int h)
	{
		width = w;
		height = h;
	}


	void Window::setApplication(Application* app)
	{
		m_app = app;
	}


	void Window::setGraphics(GraphicsSystem* graphics)
	{
		m_graphics = graphics;
	}


	Application* Window::getApplication() const
	{
		return m_app;
	}


	GraphicsSystem* Window::getGraphics() const
	{
		return m_graphics;
	}
}