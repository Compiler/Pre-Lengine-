#pragma once

#include <SDL\SDL.h>
#include <GL/glew.h>
#include <string>
namespace Lengine{

	enum WindowFlags{
		HIDDEN = 0x1,
		FULL_SCREEN = 0x2,
		BORDERLESS = 0x4

	};

	class Window{
	public:
		Window();


		int create(std::string name, int screenWidth, int screenHeight, unsigned int currentFlags);
		void setName(std::string newName);
		void displayFPS(Uint32 frames);
		void swapBuffer();

		int getWidth(){ return _screenWidth; }
		int getHeight(){ return _screenHeight; }


		~Window();

	private:
		SDL_Window* _window;
		int _screenWidth, _screenHeight;

	};

}