#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include <vector>
#include "Error.h"

namespace Lengine{

	
	//makes a call to picopng with error checking and file loading
	GLTexture ImageLoader::loadPNG(std::string filePath){

		//init all to 0
		GLTexture texture = {};

		std::vector<unsigned char> output;
		std::vector<unsigned char> inputData;

		//will be changed to width and height of image
		unsigned long width, height;


		if(!(IOManager::readFileToBuffer(filePath, inputData))){
			Error::throwException("Failed to read file to buffer in ImageLoader", -1, true);
		}

		int errorCode = decodePNG(output, width, height, &(inputData[0]), inputData.size(), true);
		if(errorCode != 0){
			Error::throwException("PICO couldnt decode PNG in ImageLoader with error " + std::to_string(errorCode), errorCode, true);
		}

		glGenTextures(1, &(texture.id));

		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &output[0]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);



		glBindTexture(GL_TEXTURE_2D, 0);


		texture.width = width;
		texture.height = height;

		return texture;
	}

}
