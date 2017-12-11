#pragma once
#include <IKeyMapper.h>

namespace Input {

	class MyKeyMapper : public IKeyMapper {
	public:
		int getKeyFor(int action) const;
	};
}