#include "AssetManager.h"

Lengine::TextureCache Lengine::AssetManager::_textureCache;

//used as a wrapper for the actual finding algo from tecture cache
Lengine::GLTexture Lengine::AssetManager::getTexture(std::string texturePath){
	return _textureCache.getTexture(texturePath);
}
