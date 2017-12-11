#pragma once

namespace Input {
	class IKeyMapper;
	class KeyInput {
		IKeyMapper* keyMapper;
		int maxActionValue;
		int _actionsThisFrame;
	public:
		bool intialize(IKeyMapper* keyMapper, int maxActionValue);
		bool shutdown();
		void update();
		int actionsThisFrame() const { return _actionsThisFrame; }
		bool actionsHotThisFrame(int actions) const;
	};
}


