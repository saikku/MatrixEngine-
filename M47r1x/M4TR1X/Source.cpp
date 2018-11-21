#include "Win32Window.h"
#include "Ref.h"
#include "OGLGraphicsSystem.h"
#include "Application.h"
#include "ElapsedTimer.h"
#include "ResourceManager.h"
#include "Input.h"
#include "Application.h"

int main(){

	int w = 800;//800
	int h = 600;//600


	Engine::Ref<Engine::Win32Window> window = new Engine::Win32Window(w, h, L"Testi ykskaks kolme");
	Engine::Ref<Engine::OGLGraphicsSystem> graphics = new Engine::OGLGraphicsSystem(window);
	window->setGraphics(graphics); // Set graphics for window

	Engine::Ref<Engine::Application> application = new Engine::Application();
	window->setApplication(application); // Set application for window

	Engine::ElapsedTimer frameTimer;



	frameTimer.Reset();
	Resource::ResourceManager *resMngr = new Resource::ResourceManager();
	//Resource::ResourceManager *kesMngr = new Resource::ResourceManager();

	// Lataa resourcetiedostot tässä
	resMngr->loadResource("../kissakuva.jpg", 32, 32);
	//kesMngr->loadResource("../koirakuva.jpg", 16, 16);

	while (window->updateMsg())
	{
		
		// updateMessages palautta true. Päivitä peliä.
		float deltaTime = frameTimer.getTime();
		frameTimer.Reset();
		application->Update(deltaTime);
	}

}