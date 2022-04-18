#pragma once

#include "DrawableObject.h"
#include <SDL_ttf.h>

class TextObject :public DrawableObject
{
private:
	unsigned int texture;

public:
	TextObject();
	~TextObject();
	void Render(glm::mat4 globalModelTransform);
	void Update(float deltaTime);
	void LoadText(string text, SDL_Color textColor, int fontSize);
	
};