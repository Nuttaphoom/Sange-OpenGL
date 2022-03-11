#pragma once
#include "Player.h"
#include "Manager.h"
#include <map>
//Create a animation object and determine its lifespan




class AnimatorManager : public Manager {
	struct AnimatorObj {
		SpriteObject* AnimationObject;
		vector<SpriteObject*> PausedObj;
		float lifespan;
	};
private:
	vector<AnimatorObj*> spriteObjectDict;
	static AnimatorManager* instance;
public:
	static AnimatorManager* GetInstance();
 

	AnimatorManager() ;

	//Responsible to "hide" (not replace) object(s) and spawn animationObj in their position with some given adjustment 
	void CreateAnimationFactory(vector<SpriteObject*> objToHide, glm::vec3 pos, glm::vec3 size, float _lifespan, string fileName,
		int row, int column, int howManyFrame, int delayBetaweenFrame);


	void Update(int deltaTime);

	virtual void Render(glm::mat4 globalModelTransform);

};

