#include "AssetManager.h"

Lengine::TextureCache Lengine::AssetManager::_textureCache;


Lengine::GLTexture Lengine::AssetManager::getTexture(std::string texturePath){
	return _textureCache.getTexture(texturePath);
}