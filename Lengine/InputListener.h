#pragma once
#include <SDL\SDL.h>
#include <stdio.h>
#include "Sprite.h"
#include <unordered_map>

namespace Lengine{

	class InputListener{
	public:
		InputListener();

		void keyPressed(unsigned int keyID);
		void keyReleased(unsigned int keyID);

		bool isKeyPressed(unsigned int keyID);


		~InputListener();


	private:
		std::unordered_map<unsigned int, bool> _keyMap;
	};

}