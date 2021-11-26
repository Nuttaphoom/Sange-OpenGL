#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class SpriteObject :public DrawableObject
{
private:
	unsigned int texture;
	int rowMax;
	int columnMax;
	int currentRow;
	int currentColumn;
	float uv[8];
	int startRow;
	int startColumn;
	int loopMax;
	int loopCount;
	int animationTime;
	int timeCount;
	bool playAnim; 

public:
	SpriteObject(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size) ;
	SpriteObject(unsigned int texture , int row, int column,glm::vec3 Pos, glm::vec3 Size);
	~SpriteObject();
	virtual void Render(glm::mat4 globalModelTransform);
	virtual void Update(int deltaTime);
	virtual void GenUV();
	virtual void SetAnimationLoop(int startRow, int startColumn, int howManyFrame, int delayBetaweenFrame,bool playanim); // 1000 = 1 second
	virtual void NextAnimation();
	virtual void SetTexture(string path);
	virtual unsigned int GetTexture();
	virtual void SetUV(float uvs[8]); 
	virtual float* GetUV(); 

};

