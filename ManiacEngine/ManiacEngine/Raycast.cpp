#include "Raycast.h"
#include "GameStateController.h"



glm::vec3 RayCast::GetOutPutPoint() {
	glm::vec3 output = p2;
	float m = (p1.y - p2.y) / (p1.x - p2.x);
	glm::vec3 curPoint = p1;

	glm::vec3 normalizeVec = glm::normalize(p2 - p1) ;  //Vector from point 1 to 2
	float IncreasedXValue = normalizeVec.x * 32;
	float IncreasedYValue = normalizeVec.y * 32;

  	while (true) { //Until collide with some entity (it will collide with p2 in the end)
		curPoint.x += IncreasedXValue; 
		curPoint.y += IncreasedYValue;
									  
 		Entity* inv = new Entity() ; 
 		inv->SetPosition(curPoint); 
		inv->SetSize(32, 32);

 		for (int c = GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().size() - 1; c >= 0; c--) {
			if (dynamic_cast<InvisibleObject*>(GameStateController::GetInstance()->currentLevel->GetInvisibleWallList()[c])->Collide_W_Entity(*inv)) {
 				return curPoint;
			}
		}
		
		delete inv ;
		if (p1.x > p2.x && curPoint.x <= p2.x)
			return p2 ;
		else if (p1.x < p2.x && curPoint.x >= p2.x)
			return p2;
 
	}
 
	return p2;
}
 
glm::vec3 RayCast::GetOutPutRayCast() {
	glm::vec3 output = p2;
	float m = (p1.y - p2.y) / (p1.x - p2.x);
	glm::vec3 curPoint = p1;



	glm::vec3 normalizeVec = glm::normalize(p2 - p1);  //Vector from point 1 to 2
	float IncreasedXValue = normalizeVec.x * 32;
	float IncreasedYValue = normalizeVec.y * 32;

	while (true) { //Until collide with some entity (it will collide with p2 in the end)
		curPoint.x += IncreasedXValue;
		curPoint.y += IncreasedYValue;

		Entity* inv = new Entity();
		inv->SetPosition(curPoint);
		inv->SetSize(32, 32);

		for (int c = GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().size() - 1; c >= 0; c--) {
			if (dynamic_cast<InvisibleObject*>(GameStateController::GetInstance()->currentLevel->GetInvisibleWallList()[c])->Collide_W_Entity(*inv)) {
				return curPoint - p1 ;
			}
		}

		delete inv;
		if (p1.x > p2.x && curPoint.x <= p2.x)
			return p2 - p1;
		else if (p1.x < p2.x && curPoint.x >= p2.x)
			return p2 - p1;

	}

	return p2 - p1;
 }

glm::vec3 RayCast::GetOutPutPointWithoutBound() {
	glm::vec3 output = p2;
	float m = (p1.y - p2.y) / (p1.x - p2.x);
	glm::vec3 curPoint = p1;

	glm::vec3 normalizeVec = glm::normalize(p2 - p1);  //Vector from point 1 to 2
	float IncreasedXValue = normalizeVec.x * 32;
	float IncreasedYValue = normalizeVec.y * 32;
	int time = 0; 
	while (time < 1000) { //Until collide with some entity (it will collide with p2 in the end)
		curPoint.x += IncreasedXValue;
		curPoint.y += IncreasedYValue;

		Entity* inv = new Entity();
		inv->SetPosition(curPoint);
		inv->SetSize(32, 32);

		for (int c = GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().size() - 1; c >= 0; c--) {
			if (dynamic_cast<InvisibleObject*>(GameStateController::GetInstance()->currentLevel->GetInvisibleWallList()[c])->Collide_W_Entity(*inv)) {
				return curPoint;
			}
		}

		delete inv;
		 
		time++; 
	}

	return p2;
}

RayCast::RayCast(glm::vec3 p1, glm::vec3 p2) {
	this->p1 = p1; 
	this->p2 = p2; 
}

bool RayCast::Collide(glm::vec3 point, DrawableObject* objects) {
	bool CollideX;
	bool CollideY;
	CollideX = point.x <= objects->GetPos().x + objects->GetSize().x / 2 && point.x >= objects->GetPos().x - objects->GetSize().x / 2;
	
	CollideY = point.y <= objects->GetPos().y + abs(objects->GetSize().y) / 2 && point.y >= objects->GetPos().y - abs(objects->GetSize().y) / 2;

 
	 
	
	return CollideX && CollideY;
}

 