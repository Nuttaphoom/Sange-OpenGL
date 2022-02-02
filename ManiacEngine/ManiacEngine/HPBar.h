
#include "GUI.h"
#include "Observer.h"

class HPBar : public GUI , public Observer {
	private :
		vector<GUI*> HPPoints; 

		string temp_fileName; int temp_row; int temp_column; 
	public : 
		 HPBar(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size);
		virtual void RespawnThisObject();
		virtual void OnNotify();  
		virtual void Render(glm::mat4 globalModelTransform);

};