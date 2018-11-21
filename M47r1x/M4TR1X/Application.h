#ifndef APPLICATION_H
#define APPLICATION_H

#include "Object.h"
#include "Ref.h"
#include <vector>
#include "ResourceManager.h"
#include <string.h>
#include <GL\glut.h>
#include <iostream>
#include <fstream>
#include "SOIL.h"
#include "Input.h"

namespace Engine{

	class Window;
	class GraphicsSystem;
	class Shader;
	class Texture2D;

	class Application :
		public Object

	{
	public:
		Application();
		~Application();

		// päivitys
		bool Update(float deltaTime);
		void Render(Window* window, GraphicsSystem* graphics);
		void changePos(int xPos, int yPos);
	private:
		float size = 0.5f;
		float dx = 0.0f;
		float dy = -0.4f;
		float depth = 0.0f;
		float velocity = 0.010f;				// "object speed"
		float velocityx = 0.004f;

		float m_totalTime;
		std::vector<Ref<Shader>> m_Shaders;
		std::vector<Ref<Texture2D>> m_Textures;


	};
}

#endif
