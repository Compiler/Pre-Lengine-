#include "InputListener.h"

namespace Lengine{

	InputListener::InputListener(){

	}

	
	//sends info from event to map
	void InputListener::keyPressed(unsigned int keyID){
		_keyMap[keyID] = true;
	}
	
	//nullifies the key pressed in previous frame
	void InputListener::keyReleased(unsigned int keyID){
		_keyMap[keyID] = false;
	}
	
	//returns the value of the keymap
	bool InputListener::isKeyPressed(unsigned int keyID){
		auto it = _keyMap.find(keyID);
		if(it != _keyMap.end())
			return it->second;

		return false;
	}













	InputListener::~InputListener(){
	}

}
