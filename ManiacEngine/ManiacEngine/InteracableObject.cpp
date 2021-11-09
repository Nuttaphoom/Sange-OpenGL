#include "InteracableObject.h"


InteracableObject::InteracableObject(string fileName, int row, int column) : SpriteObject(fileName,row,column){

}


void InteracableObject::isCalled(Entity e) {
	int CollideDetection = 0; //Check where it collide with Entity (In Entity POV) 
							  // 1 FOR TOP, 2 FOR BOTTOM, 4 FOR LEFT, AND 8 FOR RIGHT 

	if (e.GetPos().x - this->GetPos().x > 100 || e.GetPos().x - this->GetPos().x < -100)
		return;

	float LeftX_Inv_Obj = (float)this->GetPos().x - this->GetSize().x / 2;
	float RightX_Inv_Obj = (float)this->GetPos().x + this->GetSize().x / 2;

	float TOPY_Inv_Obj = (float)this->GetPos().y + this->GetSize().y * -1 / 2;
	float BOTTOMY_Inv_Obj = (float)this->GetPos().y - this->GetSize().y * -1 / 2;

	float TOP_BOTTOM_X = (float)e.GetPos().x - e.GetSize().x / 4;
	float TOP_Y = (float)e.GetPos().y + e.GetSize().y / 2 * -1;

	float Middle_1_2_X = (float)e.GetPos().x - e.GetSize().x / 2;
	float Middle_1_Y = (float)e.GetPos().y + e.GetSize().y * -1 / 4;

	float Middle_2_Y = (float)e.GetPos().y - e.GetSize().y * -1 / 4;

	float BOTTOM_Y = (float)e.GetPos().y - 1 - e.GetSize().y * -1 / 2;

	//TOP 
	if ((TOP_BOTTOM_X < RightX_Inv_Obj && TOP_BOTTOM_X > LeftX_Inv_Obj) ||
		(TOP_BOTTOM_X + e.GetSize().x / 2 < RightX_Inv_Obj && TOP_BOTTOM_X + e.GetSize().x / 2 > LeftX_Inv_Obj)) {
		if (TOP_Y > TOPY_Inv_Obj && TOP_Y < BOTTOMY_Inv_Obj) {
			CollideDetection += 1;
		}
	}

	//MIDDLE_LEFT
	if ((Middle_1_2_X < RightX_Inv_Obj && Middle_1_2_X > LeftX_Inv_Obj)) {
		if ((Middle_1_Y > TOPY_Inv_Obj && Middle_1_Y < BOTTOMY_Inv_Obj) ||
			(Middle_2_Y > TOPY_Inv_Obj && Middle_2_Y < BOTTOMY_Inv_Obj)) {
			CollideDetection += 4;
		}
	}

	//MIDDLE_RIGHT
	Middle_1_2_X += e.GetSize().x;
	if ((Middle_1_2_X < RightX_Inv_Obj && Middle_1_2_X > LeftX_Inv_Obj)) {
		if ((Middle_1_Y > TOPY_Inv_Obj && Middle_1_Y < BOTTOMY_Inv_Obj) ||
			(Middle_2_Y > TOPY_Inv_Obj && Middle_2_Y < BOTTOMY_Inv_Obj)) {
			CollideDetection += 8;
		}
	}

	//TOP 
	if ((TOP_BOTTOM_X < RightX_Inv_Obj && TOP_BOTTOM_X   > LeftX_Inv_Obj) ||
		(TOP_BOTTOM_X + e.GetSize().x / 2 < RightX_Inv_Obj && TOP_BOTTOM_X + e.GetSize().x / 2 > LeftX_Inv_Obj)) {
		if (BOTTOM_Y > TOPY_Inv_Obj && BOTTOM_Y < BOTTOMY_Inv_Obj) {
			CollideDetection += 2;
		}
	}

	if (CollideDetection > 0) {
		called();
	}
}

