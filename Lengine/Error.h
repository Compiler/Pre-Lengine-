#pragma once

#include <string>
#include <iostream>
#include <stdlib.h>
#include <SDL\SDL.h>
namespace Lengine{
	class Error{
//for uterasotior
	public:
		static void throwException(std::string errorString, int errorCode, bool quit){
			std::cout << "Error: " << errorString;
			if(quit){
				printf("Quitting with code: %d... press any key to continue", errorCode);
				int tmp;
				std::cin >> tmp;
				SDL_Quit();
				exit(errorCode);
			}
		}

		static const int SHADER = -2;


	};
}
