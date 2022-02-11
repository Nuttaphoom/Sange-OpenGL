#include "HPBar.h"
#include "Player.h"
#include "Raycast.h"

HPBar::HPBar(string fileName, int row, int column,glm::vec3 Pos, glm::vec3 Size) : GUI(fileName,row,column,Pos,Size) {
	float offsetX = 32; 
	temp_fileName = fileName; 
	temp_row = row; 
	temp_column = column; 
  	for (int i = 0; i < Player::GetInstance()->GetHP() ; i++) {
		cout << "c" << endl;
 		GUI* newP = new GUI(fileName, row, column, glm::vec3(Pos.x + offsetX * i, Pos.y, this->GetPos().z),glm::vec3(238/10,-448/10,1));
 
		HPPoints.push_back(newP); 
	}

	RayCast s = RayCast(Player::GetInstance(), Player::GetInstance()) ;
	glm::vec3 vec = s.GetOutPutRayCast(); 
	Player::GetInstance()->attach(this,0);
}
 
void HPBar::OnNotify() {
	if (HPPoints.size() > 0) {
		delete HPPoints[HPPoints.size() - 1]; 
		HPPoints.pop_back(); 
	}
}

void HPBar::Render(glm::mat4 globalModelTransform)
{
	//GUI::Render(globalModelTransform); 
	for (int i = 0; i < HPPoints.size(); i++) {
		HPPoints[i]->Render(globalModelTransform);
	}
}

void HPBar::RespawnThisObject() {
	float offsetX = 32;
	cout << "HPBAR IS BEING RESPAWNER" << endl;

	for (int i = 0; i < Player::GetInstance()->GetHP(); i++) {
 		GUI* newP = new GUI(temp_fileName, temp_row, temp_column, glm::vec3(GetPos().x + offsetX * i, GetPos().y, this->GetPos().z), glm::vec3(238 / 10, -448 / 10, 1));

		HPPoints.push_back(newP);
	}
}