#include "Window.h"
#include "Error.h"

namespace Lengine{


	Window::Window(){
	}


	//creates a window with name, dims, and flags
	int Window::create(std::string name, int screenWidth, int screenHeight, unsigned int currentFlags){

		Uint32 flags = SDL_WINDOW_OPENGL;

		if(currentFlags & WindowFlags::HIDDEN)
			flags |= SDL_WINDOW_HIDDEN;

		if(currentFlags & WindowFlags::BORDERLESS)
			flags |= SDL_WINDOW_BORDERLESS;

		if(currentFlags & WindowFlags::FULL_SCREEN)
			flags |= SDL_WINDOW_FULLSCREEN;

		_screenWidth = screenWidth;
		_screenHeight = screenHeight;

		_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, flags);

		if(_window == nullptr)
			Lengine::Error::throwException("Window initialization failed", -1, true);


		//Stores context in window, therefor delete context object asap ferg
		SDL_GLContext glContext = SDL_GL_CreateContext(_window);

		if(glContext == nullptr)
			Lengine::Error::throwException("Couldnt initialize Context", -1, true);

		if(glewInit() != GLEW_OK){
			Lengine::Error::throwException("Couldnt initialize GLEW", -1, true);
		}



		//sets to context for glClearBufferBit
		glClearColor(0.0f, 0.0f, 0.0f, 1);
		//SDL_GL_DeleteContext(glContext);




		SDL_GL_SetSwapInterval(1);
		std::printf("***   OpenG Version: %s ***", glGetString(GL_VERSION));

		return 1;
	}
	
	//sets name
	void Window::setName(std::string newName){

		SDL_SetWindowTitle(_window, newName.c_str());

	}

	//displays fps as title
	void Window::displayFPS(Uint32 frames){

		SDL_SetWindowTitle(_window, std::to_string(frames).c_str());
	}


	
	//swaps buffer
	void Window::swapBuffer(){
		//swap for double buffer
		SDL_GL_SwapWindow(_window);
	}


	Window::~Window(){
	}

}
