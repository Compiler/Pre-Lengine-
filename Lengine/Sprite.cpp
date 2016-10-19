#include "Sprite.h"
#include <cstddef>
#include "ImageLoader.h"

namespace Lengine{
	//nullifies initial args
	Sprite::Sprite(){
		//null
		_vboID = 0;

	}


	//Sends the vertex data through the buffer and binds in with the tint attrib
	void Sprite::initRect(float x, float y, float width, float height, std::string filePath, GLubyte r, GLubyte g, GLubyte b, GLubyte a){

		_x = x;
		_y = y;
		_width = width;
		_height = height;

		_entityTexture = AssetManager::getTexture(filePath);

		if(_vboID == 0){
			glGenBuffers(1, &_vboID);
		}

		vertexData[0].setPosition(_x, _y);
		vertexData[0].setUV(0, 0);

		vertexData[1].setPosition(_x, _y + _height);
		vertexData[1].setUV(0, 1);

		vertexData[2].setPosition(_x + _width, _y + _height);
		vertexData[2].setUV(1, 1);

		vertexData[3].setPosition(_x, _y);
		vertexData[3].setUV(0, 0);

		vertexData[4].setPosition(_x + _width, _y + _height);
		vertexData[4].setUV(1, 1);

		vertexData[5].setPosition(_x + _width, _y);
		vertexData[5].setUV(1, 0);



		for(int i = 0; i < 6; i++){
			vertexData[i].setColor(r, g, b, a);
		}





		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_DYNAMIC_DRAW);

		//unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		
	}
	
	//add tint attrib to the shader through the vertex
	void Sprite::setTint(GLubyte r, GLubyte g, GLubyte b, GLubyte a){

		for(int i = 0; i < 6; i++){
			vertexData[i].setColor(r, g, b, a);
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_DYNAMIC_DRAW);

		//unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);


	}

	void Sprite::update(){


	}

	//bbinds renders and unbinds
	void Sprite::render(){
		
		glBindTexture(GL_TEXTURE_2D, _entityTexture.id);

		//Sets this to the active buffer, there can only be one active at a time so
		//we do this everytime we need to render something
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);


		//as of right now we only use position so we take the first (0th) index of the array in vertex attribs
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		//tells opengl this is where we start to draw for position
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//disable it after
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		//unbind after because whatever else needs to be rendered needs to be set active too
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}



	void Sprite::setBooleans(int index, bool condition){

		_movement[index] = condition;

	}







	Sprite::~Sprite(){

		if(_vboID != 0)
			glDeleteBuffers(1, &_vboID);

	}
}
