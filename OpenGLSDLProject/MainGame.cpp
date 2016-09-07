#include "MainGame.h"
#include <Lengine\AssetManager.h>

MainGame::MainGame() :_screenHeight(480), _screenWidth(640), _gameState(Lengine::GameState::RUNNING),
_maxFPS(60)
{

	_camera.init(640, 480);
	

}


MainGame::~MainGame() {

}




void MainGame::init() {

	Lengine::init();
	
	_window.create("Lengine", 640, 480, 0);

	

	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.bindAttribute("vertexPosition", 0);
	_colorProgram.bindAttribute("vertexColor", 1);
	_colorProgram.bindAttribute("vertexUV", 2);
	_colorProgram.linkShaders();

	_batch.init();


}

void MainGame::run() {

	//first init everything
	init();
	
	while (_gameState != Lengine::GameState::EXIT) {
		Uint32 startTicks = SDL_GetTicks();
		update();
		

		render();

		calculateFPS();

		static int frameCounter = 0;
		frameCounter++;
		if(frameCounter == 10){
			_window.displayFPS(_fps);
			frameCounter = 0;
		}

		



		Uint32 frameTicks = SDL_GetTicks() - startTicks;

		if(1000.0f / _maxFPS > frameTicks){
			SDL_Delay((1000 / _maxFPS) - frameTicks);
		}
	}


	MainGame::dispose();

}

void MainGame::update() {
	
	_camera.update();
	SDL_Event evnt;
	float speed = 5.0f;
	while(SDL_PollEvent(&evnt)){
		switch(evnt.type){
		case SDL_QUIT:
			_gameState = Lengine::GameState::EXIT;
			break;

		case SDL_KEYDOWN:
			_listener.keyPressed(evnt.key.keysym.sym);
			switch(evnt.key.keysym.sym){
				case SDLK_w:
					_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, speed));
					break;

				case SDLK_s:
					_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -speed));
					break;

				case SDLK_a:
					_camera.setPosition(_camera.getPosition() + glm::vec2(-speed, 0.0f));
					break;

				case SDLK_d:
					_camera.setPosition(_camera.getPosition() + glm::vec2(speed, 0.0f));
					break;

				case SDLK_q:
					_camera.setScale(_camera.getScale() + speed);
					break;

				case SDLK_e:
					_camera.setScale(_camera.getScale() - speed);
					break;

			}
		}

	}
}

void MainGame::render() {
	glClearDepth(1.0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	_colorProgram.use();

	glActiveTexture(GL_TEXTURE0);

	GLint textureLocation = _colorProgram.getUniformLocation("tex");

	glUniform1i(textureLocation, 0);

	GLint loc = _colorProgram.getUniformLocation("cameraMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &(_camera.getMatrix()[0][0]));


	_batch.begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Lengine::GLTexture tex = Lengine::AssetManager::getTexture("Textures//Background.png");
	Lengine::Color color;
	color.a = 255;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	for(int i = 0; i < 5000; i++)
	_batch.draw(pos, uv, tex.id, 0.0f, color);

	_batch.end();

	_batch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);


	_colorProgram.unuse();

	_window.swapBuffer();
}


void MainGame::calculateFPS(){
	//iteration average
	static const int NUM_SAMPLES = 10;
	//circular buffer
	static Uint32 frameTimes[NUM_SAMPLES];
	//iteration index
	static int currentFrame = 0;

	static Uint32 prevTicks = SDL_GetTicks();
	Uint32 currentTicks;

	currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = SDL_GetTicks();

	int count;
	currentFrame++;
	if(currentFrame < NUM_SAMPLES)
		count = currentFrame;
	else
		count = NUM_SAMPLES;

	Uint32 frameTimeAverage = 0;

	for(int i = 0; i < count; i++)
		frameTimeAverage += frameTimes[i];

	frameTimeAverage /= count;

	if(frameTimeAverage > 0)
		_fps = 1000 / frameTimeAverage;
	else
		_fps = 60;

	
}



void MainGame::dispose(){
	printf("Disposing world");

	SDL_Quit();
}

