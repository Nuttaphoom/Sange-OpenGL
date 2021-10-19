#include "InvisibleObject.h"
#include "GameEngine.h" 
#include "GameObject.h" 

 void InvisibleObject::Render(glm::mat4 globalModelTransform) {
	if (this->render) {
		SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

		GLuint modelMatixId = GameEngine::GetInstance()->GetRenderer()->GetModelMatrixAttrId();
		GLuint colorId = GameEngine::GetInstance()->GetRenderer()->GetColorUniformId();
		GLuint renderModeId = GameEngine::GetInstance()->GetRenderer()->GetModeUniformId();

		if (modelMatixId == -1) {
			cout << "Error: Can't perform transformation " << endl;
			return;
		}
		if (colorId == -1) {
			cout << "Error: Can't set color " << endl;
			return;
		}
		if (renderModeId == -1) {
			cout << "Error: Can't set renderMode in ImageObject " << endl;
			return;
		}
		//vector <glm::mat4> matrixStack;

		glm::mat4 currentMatrix = this->getTransform();

		if (squareMesh != nullptr) {

			currentMatrix = globalModelTransform * currentMatrix;
			glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
			glUniform3f(colorId, color.x, color.y, color.z);
			glUniform1i(renderModeId, 0);
			squareMesh->Render();

		}
	}
}

void InvisibleObject::Update(float deltaTime) {

}

void InvisibleObject::SetRender(bool b) {
	this->render = b; 
}

bool InvisibleObject::Collide_W_Entity(Entity e) {

	bool CollideX;
	bool CollideY;

	CollideX = (float) e.GetPos().x - e.GetSize().x / 2 < (float) this->GetPos().x + this->GetSize().x / 2 && 
		(float) e.GetPos().x + e.GetSize().x / 2 > (float) this->GetPos().x - this->GetSize().x / 2 ;

	CollideY = (float)e.GetPos().y - e.GetSize().y * -1 /2 < (float) this->GetPos().y + this->GetSize().y * -1 / 2 &&
		(float)e.GetPos().y + e.GetSize().y * -1 / 2 > (float)this->GetPos().y - this->GetSize().y *-1 / 2;
 
	return  CollideX & CollideY ;
}

InvisibleObject::InvisibleObject() {
	this->color = glm::vec3(0, 1, 0); 
	this->size = glm::vec3(1, 1, 1);
	this->pos = glm::vec3(0,0,0);
}