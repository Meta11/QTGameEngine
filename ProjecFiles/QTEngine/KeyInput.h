#pragma once

namespace Input {

	class IKeyMapper;
	
	class __declspec(dllexport) KeyInput {
		IKeyMapper* keyMapper;
		int maxActionValue;
		int _actionsThisFrame;
		KeyInput() {}
		KeyInput(const KeyInput&);
		KeyInput& operator=(const KeyInput&);
		static KeyInput instance;
	public:
		bool intialize(IKeyMapper* keyMapper, int maxActionValue);
		bool shutdown();
		void update();
		int actionsThisFrame() const { return _actionsThisFrame; }
		bool actionsHot(int actions) const;
		static KeyInput& getInstance();
	};
	#define input Input::KeyInput::getInstance()
}


