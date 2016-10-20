#pragma once
#include <SDL\SDL.h>
#include <stdio.h>
#include "Sprite.h"
#include <unordered_map>

namespace Lengine{

	class InputListener{
	public:
		InputListener();

		//symamntics 
		void keyPressed(unsigned int keyID);
		void keyReleased(unsigned int keyID);

		//return value static
		bool isKeyPressed(unsigned int keyID);


		~InputListener();


	private:
		//how it is mapped
		std::unordered_map<unsigned int, bool> _keyMap;
	};

}
