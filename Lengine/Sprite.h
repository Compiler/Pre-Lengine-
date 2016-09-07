#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include "Vertex.h"
#include "GLSLProgram.h"
#include "GLTexture.h"
#include "AssetManager.h"

namespace Lengine{

	class Sprite{
	public:
		Sprite();
		~Sprite();

		void initRect(float x, float y, float width, float height, std::string filePath, GLubyte r = 255, GLubyte g = 255, GLubyte b = 255, GLubyte a = 255);
		void update();
		void render();
		void setBooleans(int index, bool condition);
		void setTint(GLubyte r, GLubyte g, GLubyte b, GLubyte a);

		const float speed = 1.0f;

		static const unsigned int UP = 0;
		static const unsigned int DOWN = 1;
		static const unsigned int RIGHT = 2;
		static const unsigned int LEFT = 3;

	private:

		float _x;
		float _y;
		float _width;
		float _height;

		float _rectTranslation[2];
		bool _movement[4];
		Vertex vertexData[6];

		GLuint _vboID;
		GLTexture _entityTexture;

	};

}