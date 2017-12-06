#pragma once
#include <Renderer.h>

namespace Rendering { class Renderable; }

class MyGame {
	Rendering::Renderer renderer;
	Rendering::Renderable* shipInstance;
	Rendering::Renderable* lerpInstance;;
public:
	bool initialize();
	void update();
};

