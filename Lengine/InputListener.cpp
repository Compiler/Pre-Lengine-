#include "InputListener.h"

namespace Lengine{

	InputListener::InputListener(){

	}

	

	void InputListener::keyPressed(unsigned int keyID){
		_keyMap[keyID] = true;
	}

	void InputListener::keyReleased(unsigned int keyID){
		_keyMap[keyID] = false;
	}

	bool InputListener::isKeyPressed(unsigned int keyID){
		auto it = _keyMap.find(keyID);
		if(it != _keyMap.end())
			return it->second;

		return false;
	}













	InputListener::~InputListener(){
	}

}