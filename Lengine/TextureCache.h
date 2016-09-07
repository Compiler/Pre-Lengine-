#pragma once

#include <map>
#include "GLTexture.h"

namespace Lengine{

	class TextureCache{
	public:
		TextureCache();


		GLTexture getTexture(std::string texturePath);



		~TextureCache();

	private:
		std::map<std::string, GLTexture> _textureMap;
	};

}