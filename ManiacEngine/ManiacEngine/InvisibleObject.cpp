#include "InvisibleObject.h"
#include "GameEngine.h" 
#include "GameObject.h" 
#include "Player.h"
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

int InvisibleObject::Collide_W_Entity(Entity e) {
	int CollideDetection = 0; //Check where it collide with Entity (In Entity POV) 
							  // 1 FOR TOP, 2 FOR BOTTOM, 4 FOR LEFT, AND 8 FOR RIGHT 
	if (e.IsPause() || e.Death()) {
		return 0;
	}
	 
	if (abs(e.GetPos().x - this->GetPos().x) > 128 || abs(e.GetPos().y - this->GetPos().y) > 128)
		return 0; 

	float enLeft, enRight, enTop, enBottom; 
	float invLeft, invRight, invTop, invBottom;
	
	enLeft = e.GetPos().x - e.collisionSize.x / 2 ;  
	enRight = e.GetPos().x + e.collisionSize.x / 2 ; 
	enTop = e.GetPos().y + abs(e.collisionSize.y) / 2 ; 
	enBottom = e.GetPos().y - abs(e.collisionSize.y) / 2;   

	invLeft = GetPos().x - GetSize().x / 2;  
	invRight = GetPos().x + GetSize().x / 2 ; 
	invTop = GetPos().y + abs(GetSize().y) / 2; 
	invBottom = GetPos().y - abs(GetSize().y) / 2; 

	float LeftX_Inv_Obj = (float)this->GetPos().x - this->GetSize().x / 2;
	float RightX_Inv_Obj = (float)this->GetPos().x + this->GetSize().x / 2;

	float TOPY_Inv_Obj = (float) this->GetPos().y + abs(this->GetSize().y)  / 2;
	float BOTTOMY_Inv_Obj = (float) this->GetPos().y - abs(this->GetSize().y) / 2;

	float TOP_BOTTOM_X = (float)e.GetPos().x - e.collisionSize.x / 4; 
	float TOP_Y = (float)e.GetPos().y + abs(e.collisionSize.y) / 2 ; 

	float Middle_1_2_X = (float)e.GetPos().x - e.collisionSize.x / 2 ; 
 
	float Middle_1_Y = (float)e.GetPos().y + abs(e.collisionSize.y) / 4; 

 	float Middle_2_Y = (float)e.GetPos().y - abs(e.collisionSize.y) / 4; 

	float BOTTOM_Y = (float) e.GetPos().y - 1 - abs(e.collisionSize.y )  / 2 ;

	//TOP 
	if ((TOP_BOTTOM_X < RightX_Inv_Obj && TOP_BOTTOM_X > LeftX_Inv_Obj) ||
		(TOP_BOTTOM_X + e.collisionSize.x / 2 < RightX_Inv_Obj && TOP_BOTTOM_X + e.collisionSize.x / 2 > LeftX_Inv_Obj)) {
		if (TOP_Y < TOPY_Inv_Obj && TOP_Y > BOTTOMY_Inv_Obj) {
			CollideDetection += 1;
		}
	}

	//MIDDLE_LEFT
	if ((Middle_1_2_X < RightX_Inv_Obj && Middle_1_2_X > LeftX_Inv_Obj)) {
		if ( (Middle_1_Y < TOPY_Inv_Obj && Middle_1_Y > BOTTOMY_Inv_Obj) || 
			(Middle_2_Y < TOPY_Inv_Obj && Middle_2_Y > BOTTOMY_Inv_Obj)  ){
			CollideDetection += 4;
		}
	}

	//MIDDLE_RIGHT
	Middle_1_2_X = (float)e.GetPos().x + e.collisionSize.x / 2    ;
	if ((Middle_1_2_X < RightX_Inv_Obj && Middle_1_2_X > LeftX_Inv_Obj)) {
		if ((Middle_1_Y < TOPY_Inv_Obj && Middle_1_Y > BOTTOMY_Inv_Obj) ||
			(Middle_2_Y < TOPY_Inv_Obj && Middle_2_Y > BOTTOMY_Inv_Obj)) {
			CollideDetection += 8;
 		}
	}
 	
	//BOT 
	if ((TOP_BOTTOM_X < RightX_Inv_Obj && TOP_BOTTOM_X   > LeftX_Inv_Obj) ||
		(TOP_BOTTOM_X + e.collisionSize.x / 2 < RightX_Inv_Obj && TOP_BOTTOM_X + e.collisionSize.x / 2 > LeftX_Inv_Obj)) {
		if (BOTTOM_Y <= TOPY_Inv_Obj && BOTTOM_Y >= BOTTOMY_Inv_Obj) {
 			CollideDetection += 2;
		}
	}

  	return  CollideDetection; 
}
 
InvisibleObject::InvisibleObject() {
	climbable = true ; 
	this->color = glm::vec3(0, 1, 0);
	this->size = glm::vec3(1, 1, 1);
	this->pos = glm::vec3(0, 0, 0);
	this->render = false;
}

InvisibleObject::InvisibleObject(bool c) {
	climbable = c; 
	this->color = glm::vec3(0, 1, 0); 
	this->size = glm::vec3(1, 1, 1);
	this->pos = glm::vec3(0,0,0);
	this->render = false; 
}

bool InvisibleObject::IsClimbable() {
	return climbable; 
}