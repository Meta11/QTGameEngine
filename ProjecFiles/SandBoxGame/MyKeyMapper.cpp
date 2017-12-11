#include <Windows.h>
#include "MyKeyMapper.h"
#include "MyMenuChoice.h"

namespace Input {

	int MyKeyMapper::getKeyFor(int action) const {
		switch (action) {
			case Accelerate:
				return VK_UP;
			case RotateLeft:
				return VK_LEFT;
			case RotateRight:
				return VK_RIGHT;
		}
		return -1;
	}
}