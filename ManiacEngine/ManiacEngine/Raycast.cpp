#include "Raycast.h"
#include "GameStateController.h"


glm::vec3 RayCast::GetOutPutPoint() {
	vector<DrawableObject*> collidedObjs;
	glm::vec3 output = p2;
	float m = (p1.y - p2.y) / (p1.x - p2.x);
	glm::vec3 curPoint = p1;
	float curDependentValue = 0;
	bool finding = true;

	if (abs(m) <= 1) { //X is independent 
		curDependentValue = curPoint.y;
		while (collidedObjs.size() == 0) { //Until collide with some entity (it will collide with p2 in the end)
			curPoint.x += p1.x - p2.x > 0 ? -64 : 64;
			curDependentValue += p1.y - p2.y > 0 ? 1 / m : -1 / m;
			float decision = (int)curDependentValue % 64;
			if (decision > 32) /*Round up*/ {
				curPoint.y = curDependentValue + (64 - decision);
			}
			else   /*Round down*/ {
				curPoint.y = curDependentValue - decision;
			}

			if (p1.y - p2.y == 0) { curPoint.y = p1.y; };

			for (int c = 0; c < GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().size(); c++) {
				if (Collide(curPoint, GameStateController::GetInstance()->currentLevel->GetInvisibleWallList()[c])) {
					collidedObjs.push_back(GameStateController::GetInstance()->currentLevel->GetInvisibleWallList()[c]);
					return curPoint;
				}
			}

			if (p1.x > p2.x && curPoint.x <= p2.x)
				return p2 ;

			else if (p1.x < p2.x && curPoint.x >= p2.x)
				return p2;
		}
	}
	else if (abs(m) > 1) { //Y is independent 
		curDependentValue = curPoint.x;
		while (collidedObjs.size() == 0) { //Until collide with some entity (it will collide with p2 in the end)
			curPoint.y += p1.y - p2.y > 0 ? -64 : 64;
			curDependentValue += p1.x - p2.x > 0 ? 1 / m : -1 / m;
			float decision = (int)curDependentValue % 64;
			if (decision > 32) /*Round up*/ {
				curPoint.x = curDependentValue + (64 - decision);
			}
			else /*Round down*/ {
				curPoint.x = curDependentValue - decision;
			}

			if (p1.x == p2.x) curPoint.x = p1.x;

			for (int c = 0; c < GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().size(); c++) {
				if (Collide(curPoint, GameStateController::GetInstance()->currentLevel->GetInvisibleWallList()[c])) {
 					return curPoint; 
 				}
			}

			if (p1.y > p2.y && curPoint.y <= p2.y) {
				cout << "return 1" << endl; 
				return p2;
			}
			else if (p1.y < p2.y && curPoint.y >= p2.y) {
				cout << "return 2" << endl;
				return p2;
			}
		}
	}

	return p2;

}
 
glm::vec3 RayCast::GetOutPutRayCast() {
	//Return vector 
	vector<DrawableObject*> collidedObjs;
	glm::vec3 output = p2  ;
	float m = (p1.y - p2.y) / (p1.x - p2.x);
	glm::vec3 curPoint = p1 ;
	float curDependentValue = 0;
	bool finding = true;

	if (abs(m) <= 1) { //X is independent 
		curDependentValue = curPoint.y;
		while (collidedObjs.size() == 0) { //Until collide with some entity (it will collide with p2 in the end)
			curPoint.x += p1.x - p2.x > 0 ? -64 : 64;
			curDependentValue += p1.y - p2.y > 0 ? 1 / m : -1 / m;
			float decision = (int)curDependentValue % 64;
			if (decision > 32) /*Round up*/ {
				curPoint.y = curDependentValue + (64 - decision);
			}
			else   /*Round down*/ {
				curPoint.y = curDependentValue - decision;
			}

			if (p1.y - p2.y == 0) { curPoint.y = p1.y; };
 
			for (int c = 0; c < GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().size(); c++) {
				if (Collide(curPoint, GameStateController::GetInstance()->currentLevel->GetInvisibleWallList()[c])) {
					collidedObjs.push_back(GameStateController::GetInstance()->currentLevel->GetInvisibleWallList()[c]);
					break;
				}
			}

			if (p1.x > p2.x && curPoint.x <= p2.x)
				return glm::vec3(abs(p1.x - p2.x), abs(p1.y - p2.y), 1);

			else if (p1.x < p2.x && curPoint.x >= p2.x)
				return glm::vec3(abs(p1.x - p2.x), abs(p1.y - p2.y), 1);

		}
	}
	else if (abs(m) > 1) { //Y is independent 
		curDependentValue = curPoint.x;
		while (collidedObjs.size() == 0) { //Until collide with some entity (it will collide with p2 in the end)
			curPoint.y += p1.y - p2.y > 0 ? -64 : 64;
			curDependentValue += p1.x - p2.x > 0 ? 1 / m : -1 / m;
			float decision = (int)curDependentValue % 64;
			if (decision > 32) /*Round up*/ {
				curPoint.x = curDependentValue + (64 - decision);
			}
			else /*Round down*/ {
				curPoint.x = curDependentValue - decision;
			}

			if (p1.x == p2.x) curPoint.x = p1.x;

			for (int c = 0; c < GameStateController::GetInstance()->currentLevel->GetInvisibleWallList().size(); c++) {
				if (Collide(curPoint, GameStateController::GetInstance()->currentLevel->GetInvisibleWallList()[c])) {
					collidedObjs.push_back(GameStateController::GetInstance()->currentLevel->GetInvisibleWallList()[c]);
					break;
				}
			}

			if (p1.y > p2.y && curPoint.y <= p2.y) {
 				return glm::vec3(abs(p1.x - p2.x), abs(p1.y - p2.y), 1);
			}
			else if (p1.y < p2.y && curPoint.y >= p2.y) {
 
				return glm::vec3(abs(p1.x - p2.x), abs(p1.y - p2.y), 1);
			}
		}
	}


	for (auto i = collidedObjs.begin(); i != collidedObjs.end(); i++) {
		output = glm::vec3((*i)->GetPos().x, (*i)->GetPos().y, 1);
	}

	return output;
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

 