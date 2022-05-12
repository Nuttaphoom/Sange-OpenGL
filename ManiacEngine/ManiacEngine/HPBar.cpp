#include "HPBar.h"
#include "Player.h"
HPBar::HPBar(string fileName, int row, int column,glm::vec3 Pos, glm::vec3 Size) : GUI(fileName,row,column,Pos,Size) {
	float offsetX = 32; 
	temp_fileName = fileName; 
	temp_row = row; 
	temp_column = column; 
  	for (int i = 0; i < Player::GetInstance()->GetHP() ; i++) {
 		GUI* newP = new GUI(fileName, row, column, glm::vec3(Pos.x + offsetX * i, Pos.y, this->GetPos().z),glm::vec3(238/10,-448/10,1));
 
		HPPoints.push_back(newP); 
	}

	Player::GetInstance()->attach(this,0);
}
 
void HPBar::OnNotify() {
 
}

void HPBar::Render(glm::mat4 globalModelTransform)
{
	for (int i = 1 ; i < HPPoints.size()  ; i++) {
		HPPoints[i]->Render(globalModelTransform);
	}
}

void HPBar::Update(int deltaTime) {
	for (int i = 0; i < HPPoints.size(); i++) {
		HPPoints[i]->SetPause(true);
		cout << "Player::GetInstance()->GetHP() : " << Player::GetInstance()->GetHP() << endl;
		if (Player::GetInstance()->GetHP() > i)
			HPPoints[i]->SetPause(false);
	}
}

void HPBar::RespawnThisObject() {
	float offsetX = 32;
	for (int i = 0; i < Player::GetInstance()->GetHP(); i++) {
 		GUI* newP = new GUI(temp_fileName, temp_row, temp_column, glm::vec3(GetPos().x + offsetX * i, GetPos().y, this->GetPos().z), glm::vec3(238 / 10, -448 / 10, 1));

		HPPoints.push_back(newP);
	}
}