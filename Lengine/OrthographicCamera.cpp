#include "OrthographicCamera.h"
#include <iostream>
namespace Lengine{

	OrthographicCamera::OrthographicCamera() : _position(0.0f, 0.0f), _camMatrix(1.0f), _scale(1), _update(true), _viewport(640, 480)
	{
		
		
	}

	void OrthographicCamera::init(float width, float height){

		_viewport.x = width;
		_viewport.y = height;

		_orthoMatrix = glm::ortho(0.0f, _viewport.x, 0.0f, _viewport.y);

		std::cout << _viewport.x << ", " << _viewport.y << std::endl;
		
	}


	void OrthographicCamera::update(){
		if(_update){
			glm::vec3 translate(-_position.x, -_position.y, 0.0f);
			_camMatrix = glm::translate(_orthoMatrix, translate);
			glm::vec3 scale(_scale, _scale, 0.0f);
			_camMatrix = glm::scale(_camMatrix, scale);


			_update = false;
		}


	}


	OrthographicCamera::~OrthographicCamera(){
	}
}