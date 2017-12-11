#include <Windows.h>
#include "KeyInput.h"
#include <IKeyMapper.h>

namespace Input {

	bool KeyInput::intialize(IKeyMapper* keyMapper, int maxActionValue) {
		if (keyMapper == nullptr || maxActionValue < 0)
			return false;
		this->keyMapper = keyMapper;
		this->maxActionValue = maxActionValue;
		return true;
	}
	bool KeyInput::shutdown() {
		return true;
	}

	void KeyInput::update() {
		_actionsThisFrame = 0;

		int possibleAction = 1;
		while (possibleAction != maxActionValue) {
			int key = keyMapper->getKeyFor(possibleAction);
			if (GetAsyncKeyState(key))
				_actionsThisFrame |= possibleAction;
			possibleAction <<= 1;
		}
	}

	bool KeyInput::actionsHotThisFrame(int actions) const {
		return (_actionsThisFrame & actions) == actions;
	}
}