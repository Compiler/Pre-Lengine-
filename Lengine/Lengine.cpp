#include <SDL\SDL.h>
#include <GL\glew.h>
#include "Lengine.h"

namespace Lengine{

	//ititializes externals
	int init(){
	
		//init sdl2
		SDL_Init(SDL_INIT_EVERYTHING);
	
		//use double buffer
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}

}
