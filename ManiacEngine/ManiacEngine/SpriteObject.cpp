
#include "SpriteObject.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


SpriteObject::SpriteObject(string fileName, int row, int column,glm::vec3 Pos, glm::vec3 Size)
{
 	SetSize(Size.x, Size.y); 
	SetPosition(Pos); 

	 
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(fileName);

	this->rowMax = row;
	this->columnMax = column;
	this->currentRow = 0;
	this->currentColumn = 0;
	this->GenUV();

	this->startRow = 0;
	this->startColumn = 0;
	this->loopMax = 1;
	this->loopCount = 0;
	this->animationTime = 0;
	this->timeCount = 0;

	this->Pause = false;
} 

SpriteObject::SpriteObject(unsigned int texture,int row, int column, glm::vec3 Pos, glm::vec3 Size)
{
	SetSize(Size.x, Size.y);
	SetPosition(Pos);
	this->texture = texture; 

	this->rowMax = row;
	this->columnMax = column;
	this->currentRow = 0;
	this->currentColumn = 0;
	this->GenUV();

	this->startRow = 0;
	this->startColumn = 0;
	this->loopMax = 1;
	this->loopCount = 0;
	this->animationTime = 0;
	this->timeCount = 0;
}


SpriteObject::~SpriteObject()
{
}

void SpriteObject::Render(glm::mat4 globalModelTransform)
{
	
	SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

	GLuint modelMatixId = GameEngine::GetInstance()->GetRenderer()->GetModelMatrixAttrId();
	GLuint modeId = GameEngine::GetInstance()->GetRenderer()->GetModeUniformId();

	glBindTexture(GL_TEXTURE_2D, texture);
	if (modelMatixId == -1) {
		cout << "Error: Can't perform transformation " << endl;
		return;
	}

	glm::mat4 currentMatrix = this->getTransform();
 

	if (squareMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform1i(modeId, 1);
		squareMesh->AdjustTexcoord(uv);
		squareMesh->Render();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SpriteObject::Update(int deltaTime)
{
	if (IsPause())
		return;

	timeCount += deltaTime;
	if (timeCount > animationTime && playAnim)
	{
		this->NextAnimation();
		this->GenUV();
		timeCount = 0;
	}
}


void SpriteObject::GenUV()
{
	uv[0] = currentColumn / (columnMax * 1.0f);
	uv[1] = currentRow / (rowMax * 1.0f);

	uv[2] = (currentColumn + 1) / (columnMax * 1.0f);
	uv[3] = currentRow / (rowMax * 1.0f);

	uv[4] = (currentColumn + 1) / (columnMax * 1.0f);
	uv[5] = (currentRow + 1) / (rowMax * 1.0f);

	uv[6] = currentColumn / (columnMax * 1.0f);
	uv[7] = (currentRow + 1) / (rowMax * 1.0f);
}

void SpriteObject::SetAnimationLoop(int startRow, int startColumn, int howManyFrame, int delayBetaweenFrame,bool playAnim = true)
{
	timeCount = 0;
	this->startRow = startRow;
	this->startColumn = startColumn;
	this->loopMax = howManyFrame;
	this->loopCount = 0;
	this->animationTime = delayBetaweenFrame;
	this->playAnim = playAnim; 

	currentColumn = startColumn;
	currentRow = startRow;

	GenUV();
}

void SpriteObject::NextAnimation()
{
	loopCount++;
	if (loopCount < loopMax)
	{
		currentColumn++;
		if (currentColumn == columnMax)
		{
			currentColumn = 0;
			currentRow++;
			if (currentRow == rowMax)
			{
				currentRow = 0;
			}
		}
	}
	else
	{
		currentRow = startRow;
		currentColumn = startColumn;
		loopCount = 0;
	}

}
void SpriteObject::SetTexture(string path)
{
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}

unsigned int SpriteObject::GetTexture() {
	return texture; 
}

void SpriteObject::SetUV(float uvs[8]) {
	for (int i = 0; i < 8; i++) this->uv[i] = uvs[i]; 
}

float* SpriteObject::GetUV() {
	return uv;
}

bool SpriteObject::IsPause() {
	return this->Pause;
}

void SpriteObject::SetPause(bool b) {
	this->Pause = b ;
}