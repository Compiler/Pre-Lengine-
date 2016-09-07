#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <Lengine\GameState.h>
#include <Lengine\InputListener.h>
#include <stdlib.h>
#include <Lengine\Error.h>
#include <Lengine\Sprite.h>
#include <Lengine\GLSLProgram.h>
#include <Lengine\Window.h>
#include <Lengine\Lengine.h>
#include <Lengine\OrthographicCamera.h>
#include <glm\glm.hpp>
#include <Lengine\SpriteBatch.h>

class MainGame{
public:


	MainGame();

	void run();



	~MainGame();


private:

	Lengine::Window _window;
	Lengine::GameState _gameState;
	Lengine::GLSLProgram _colorProgram;
	Lengine::OrthographicCamera _camera;
	Lengine::SpriteBatch _batch;
	Lengine::InputListener _listener;

	int _screenWidth;
	int _screenHeight;

	Uint32 _fps;
	Uint32 _frameTime;
	Uint32 _maxFPS;

	void init();
	void render();
	void update();
	void dispose();
	void calculateFPS();


};
