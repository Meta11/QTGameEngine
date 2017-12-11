#include <Windows.h>
#include "MyKeyMapper.h"
#include "MyMenuChoice.h"

namespace Input {

	int MyKeyMapper::getKeyFor(int action) const {
		switch (action) {
			case VK_UP:
				return Accelerate;
			case VK_LEFT:
				return RotateLeft;
			case VK_RIGHT:
				return RotateRight;
		}
		return -1;
	}
}