#include "TextObject.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"

TextObject::TextObject()
{
	SetPause(false); 

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


TextObject::~TextObject()
{

}

void TextObject::Update(float deltaTime)
{
}

void TextObject::LoadText(string text, SDL_Color textColor, int fontSize )
{
	glBindTexture( GL_TEXTURE_2D, texture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

 
	TTF_Font * font = TTF_OpenFont("font.ttf", fontSize);
	if (font)
	{
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text.c_str(), textColor);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surfaceMessage->w, surfaceMessage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surfaceMessage->pixels);
		this->SetSize(surfaceMessage->w, -surfaceMessage->h);
		SDL_FreeSurface(surfaceMessage);
		TTF_CloseFont(font);
	}
	else
	{
		cout << "Error: " << TTF_GetError() << endl;
		return;
	}
}

WorldTextObject::WorldTextObject()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

WorldTextObject::~WorldTextObject()
{

}

void WorldTextObject::LoadText(string text, SDL_Color textColor, int fontSize)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	TTF_Font* font = TTF_OpenFont("font.ttf", fontSize);
	if (font)
	{
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text.c_str(), textColor);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surfaceMessage->w, surfaceMessage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surfaceMessage->pixels);
		this->SetSize(surfaceMessage->w, -surfaceMessage->h);
		SDL_FreeSurface(surfaceMessage);
		TTF_CloseFont(font);
	}
	else
	{
		cout << "Error: " << TTF_GetError() << endl;
		return;
	}
}

void WorldTextObject::Update(float deltaTime)
{
}