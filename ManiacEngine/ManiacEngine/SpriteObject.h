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
	SpriteObject(string fileName, int row, int column) ;
	SpriteObject(unsigned int texture , int row, int column);
	~SpriteObject();
	void Render(glm::mat4 globalModelTransform);
	void Update(int deltaTime);
	void GenUV();
	void SetAnimationLoop(int startRow, int startColumn, int howManyFrame, int delayBetaweenFrame,bool playanim); // 1000 = 1 second
	void NextAnimation();
	void SetTexture(string path);
	void SetUV(float uvs[8]); 

};

