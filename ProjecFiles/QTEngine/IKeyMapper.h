#pragma once

namespace Input {

	class IKeyMapper {
	public:
		virtual int getKeyFor(int action) const = 0;
	};
}
