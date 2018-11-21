#include "Application.h"
#include "GraphicsSystem.h"
#include "Window.h"
#include <stdio.h>

#include <math.h>
#include <GLES2\gl2.h>
#include "Shader.h"
#include "Texture2D.h"
#include <iostream>

namespace Engine{

	void Application::changePos(int x, int y)
	{
		dx += x*velocity;
		dy += y*velocity;
		std::cout << dx << "\n";

	}


	Application::Application() :
		Object()
		, m_totalTime(0.0f)
	{

		char texturedVertexShader[] =
			"attribute vec4 vPosition;    \n"
			"attribute vec2 vTexCoord;    \n"
			"varying vec2 texCoord;       \n"
			"void main()                  \n"
			"{                            \n"
			"   gl_Position = vPosition;  \n"
			"   texCoord = vTexCoord;     \n"
			"}                            \n";

		char texturedFragmentShader[] =
			"precision mediump float;                         \n"
			"uniform sampler2D texture;                       \n"
			"varying vec2 texCoord;                           \n"
			"void main()                                      \n"
			"{                                                \n"
			"  gl_FragColor = texture2D(texture, texCoord);   \n"
			"}                                                \n";
		m_Shaders.push_back(new Shader(texturedVertexShader, texturedFragmentShader));

		// Create 2x2 Image, 3 bytes per pixel (R, G, B)
		GLubyte pixels[4 * 3] =
		{
			255, 0, 0, // Red
			0, 255, 0, // Green
			0, 0, 255, // Blue
			255, 255, 0  // Yellow
		};


		m_Textures.push_back(new Texture2D(2, 2, 3, pixels));

	}



	Application::~Application()
	{
	}

	bool Application::Update(float deltaTime)
	{
		m_totalTime += deltaTime;
		

		// Liikuttaa "kissakuvaa" ylösalas
		if (dy > 0.5f){
			velocity = velocity *(-1);
			
		}
		if (dy < -1.0f){
			velocity = velocity * (-1);

		}
		std::cout << dy << std::endl;
		dy = dy + velocity;

		if (dx < 0.5f){
			velocityx = velocityx * (-1);
		}

		if (dx > -1.0f){
			velocityx = velocityx * (-1.00009);
		}
		dx = dx + velocityx;
		// tähän väliin collision checkit




		return true;

	}

	void Application::Render(Window* window, GraphicsSystem* graphics){
		graphics->clearScreen(0, 0, 0);



		// Texture coordinates, whose origin (0,0) is top-left -corner.
		GLfloat texCoords[] = {
			0, 0,			 	// Vertex 0
			0, 1,				// Vertex 1
			1, 1,				// Vertex 2
			1, 0,				// Vertex 3
			1, 1,				// Vertex 4
			0, 0					// Vertex 5
		};

		GLfloat quad[] = {
			dx + 0.0f, dy + size, depth,	// Vertex 0
			dx + 0.0f, dy + 0.0f, depth,	// Vertex 1
			dx + size, dy + 0.0f, depth,	// Vertex 2
			dx + size, dy + size, depth,	// Vertex 3
			dx + size, dy + 0.0f, depth,	// Vertex 4
			dx + 0.0f, dy + size, depth		// Vertex 5
		};
		graphics->drawObject(m_Shaders[0], texCoords, quad, 6);

		// Swap buffers
		graphics->swapBuffers();

	}

}
