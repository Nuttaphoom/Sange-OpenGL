#include "HPBar.h"
#include "Player.h"
HPBar::HPBar(string fileName, int row, int column,glm::vec3 Pos, glm::vec3 Size,glm::vec3 pos) : GUI(fileName,row,column,Pos,Size) {
	float offsetX = 32; 
	temp_fileName = fileName; 
	temp_row = row; 
	temp_column = column; 
  	for (int i = 0; i < Player::GetInstance()->GetHP() ; i++) {
		cout << "c" << endl;
 		GUI* newP = new GUI(fileName, row, column, glm::vec3(pos.x + offsetX * i, pos.y, this->GetPos().z),glm::vec3(238/10,-448/10,1));
 
		HPPoints.push_back(newP); 
	}

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
	for (int i = 0; i < Player::GetInstance()->GetHP(); i++) {
		GUI* newP = new GUI(temp_fileName, temp_row, temp_column, glm::vec3(pos.x + offsetX * i, pos.y, this->GetPos().z), glm::vec3(238 / 10, -448 / 10, 1));

		HPPoints.push_back(newP);
	}
}