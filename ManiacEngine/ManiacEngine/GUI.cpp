#include "GUI.h" 

//Test function that can be called for specific GUI object in Update function
void UPDATE_TEST(float deltaTime) {
	cout << "test" << endl;
}

void GUI::Render(glm::mat4 globalModelTransform)
{
	SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

	GLuint modelMatixId = GameEngine::GetInstance()->GetRenderer()->GetModelMatrixAttrId();
	GLuint renderModeId = GameEngine::GetInstance()->GetRenderer()->GetModeUniformId();

	if (modelMatixId == -1) {
		cout << "Error: Can't perform transformation " << endl;
		return;
	}
	if (renderModeId == -1) {
		cout << "Error: Can't set renderMode in ImageObject " << endl;
		return;
	}

	vector <glm::mat4> matrixStack;

	//#Note 1 Instead of drawing image directly, we translate and scale it according to camera offset first.
	glm::mat4 currentMatrix = glm::mat4(1);
	currentMatrix = glm::translate(currentMatrix, Camera::GetInstance()->GetCamOffset());
	currentMatrix = glm::scale(currentMatrix, GetSize() / Camera::GetInstance()->GetZoomOffset());
	currentMatrix = glm::translate(currentMatrix, glm::vec3(GetPos().x / GetSize().x, GetPos().y / GetSize().y, 0));

	//currentMatrix += glm::translate(currentMatrix, GUIPos);
	cout << "T";
	//currentMatrix =   s  ;
	if (squareMesh != nullptr) {
		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform1i(renderModeId, 1);
		glBindTexture(GL_TEXTURE_2D, SpriteObject::GetTexture());
		squareMesh->ResetTexcoord();
		squareMesh->Render();

	}
}

void GUI::Update(float deltaTime) {
 	if (this->GUIname == GUIName::Button) {
		UPDATE_TEST(deltaTime); 
	}

}


 

