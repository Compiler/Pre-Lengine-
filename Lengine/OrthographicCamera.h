#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace Lengine{

	class OrthographicCamera{
	public:
		OrthographicCamera();


		void update();
		void init(float width, float height);

		void setPosition(const glm::vec2& newPosition){ _position = newPosition; _update = true; }
		void setScale(float newScale){ _scale = newScale; _update = true; }

		float getScale(){ return _scale; }
		glm::vec2 getPosition(){ return _position; }
		glm::mat4 getMatrix(){ return _camMatrix; }

		~OrthographicCamera();

	private:
		bool _update;
		float _scale;
		glm::vec2 _position;
		glm::vec2 _viewport;
		glm::mat4 _camMatrix;
		glm::mat4 _orthoMatrix;

	};

}

