#include "GUI.h"
#include "Observer.h"

class HPBar : public GUI , public Observer {
	private :
		vector<GUI*> HPPoints; 
	public : 
		HPBar(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 pos);
		void OnNotify();  
		void Render(glm::mat4 globalModelTransform);

};