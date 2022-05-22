#include "InteractableObject.h"
#include "GameStateController.h"
 
InteractableObject::InteractableObject(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 ColliderSize) : SpriteObject(fileName,row,column,Pos,Size) , ColliderSize(ColliderSize){
	feedbackImage = new SpriteObject("../Resource/Texture/GUI/InteractFeedback.png", 1, 1, glm::vec3(Pos.x,Pos.y + 100,Pos.z), glm::vec3(64,-64,1));
	feedbackImage->SetPause(true); 
	GameStateController::GetInstance()->currentLevel->AddObjectList(feedbackImage); 
}

void InteractableObject::RespawnThisObject() {

}

void InteractableObject::HandleKey(char k) {
	
}

void InteractableObject::Update(int deltaTime) {
	SpriteObject::Update(deltaTime); 

	if (InCollideRadius(this, Player::GetInstance())> 0) {
		feedbackImage->SetPause(false);
	}
	else {
		feedbackImage->SetPause(true);

	}
}

 
void InteractableObject::Called() {

}

void InteractableObject::isCalled(Entity* e) {
 	if (InCollideRadius(this,e) > 0) {
 		Called();
	}
}

int InteractableObject::InCollideRadius(InteractableObject* in,Entity *en) {
	int CollideDetection = 0; //Check where it collide with Entity (In Entity POV) 
						  // 1 FOR TOP, 2 FOR BOTTOM, 4 FOR LEFT, AND 8 FOR RIGHT 

	Entity e = *en; 

	if (abs(e.GetPos().x - this->GetPos().x) > 128 || abs(e.GetPos().y - this->GetPos().y) > 128)
		return 0;

	float enLeft, enRight, enTop, enBottom;
	float invLeft, invRight, invTop, invBottom;

	enLeft = e.GetPos().x - e.collisionSize.x / 2;
	enRight = e.GetPos().x + e.collisionSize.x / 2;
	enTop = e.GetPos().y + abs(e.collisionSize.y) / 2;
	enBottom = e.GetPos().y - abs(e.collisionSize.y) / 2;

	invLeft = in->GetPos().x - in->GetSize().x / 2;
	invRight = in->GetPos().x + in->GetSize().x / 2;
	invTop = in->GetPos().y + abs(in->GetSize().y) / 2;
	invBottom = in->GetPos().y - abs(in->GetSize().y) / 2;

	float LeftX_Inv_Obj = (float)in->GetPos().x - in->GetSize().x / 2;
	float RightX_Inv_Obj = (float)in->GetPos().x + in->GetSize().x / 2;

	float TOPY_Inv_Obj = (float)in->GetPos().y + abs(in->GetSize().y) / 2;
	float BOTTOMY_Inv_Obj = (float)in->GetPos().y - abs(in->GetSize().y) / 2;

	float TOP_BOTTOM_X = (float)e.GetPos().x - e.collisionSize.x / 4;
	float TOP_Y = (float)e.GetPos().y + abs(e.collisionSize.y) / 2;

	float Middle_1_2_X = (float)e.GetPos().x - e.collisionSize.x / 2;

	float Middle_1_Y = (float)e.GetPos().y + abs(e.collisionSize.y) / 4;

	float Middle_2_Y = (float)e.GetPos().y - abs(e.collisionSize.y) / 4;

	float BOTTOM_Y = (float)e.GetPos().y - 1 - abs(e.collisionSize.y) / 2;

	//TOP 
	if ((TOP_BOTTOM_X < RightX_Inv_Obj && TOP_BOTTOM_X > LeftX_Inv_Obj) ||
		(TOP_BOTTOM_X + e.collisionSize.x / 2 < RightX_Inv_Obj && TOP_BOTTOM_X + e.collisionSize.x / 2 > LeftX_Inv_Obj)) {
		if (TOP_Y < TOPY_Inv_Obj && TOP_Y > BOTTOMY_Inv_Obj) {
			CollideDetection += 1;
		}
	}

	//MIDDLE_LEFT
	if ((Middle_1_2_X < RightX_Inv_Obj && Middle_1_2_X > LeftX_Inv_Obj)) {
		if ((Middle_1_Y < TOPY_Inv_Obj && Middle_1_Y > BOTTOMY_Inv_Obj) ||
			(Middle_2_Y < TOPY_Inv_Obj && Middle_2_Y > BOTTOMY_Inv_Obj)) {
			CollideDetection += 4;
		}
	}

	//MIDDLE_RIGHT
	Middle_1_2_X = (float)e.GetPos().x + e.collisionSize.x / 2;
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
