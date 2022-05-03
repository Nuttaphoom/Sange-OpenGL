#pragma once

#include "GUI.h"
#include <SDL_ttf.h>

class TextObject :public GUI
{
private:
	unsigned int texture;

public:
	TextObject();
	~TextObject();
	void Render(glm::mat4 globalModelTransform);
	void Update(float deltaTime);
	void LoadText(string text, SDL_Color textColor, int fontSize );
};

class WorldTextObject : public DrawableObject {
private:
	unsigned int texture;

public:
	WorldTextObject();
	~WorldTextObject();
 	void Update(float deltaTime);
	void LoadText(string text, SDL_Color textColor, int fontSize);
};