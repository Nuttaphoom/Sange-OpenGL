#pragma once

class Manager {
	
public:
	virtual void Update(int deltaTime) = 0 ;
	virtual void Render(glm::mat4 globalModelTransform) = 0 ;
};



