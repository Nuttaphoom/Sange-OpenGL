#pragma once
#include "Player.h"
#include "Manager.h"
#include <map>
//Create a animation object and determine its lifespan




class AnimatorManager : public Manager {
	struct AnimatorObj {
		SpriteObject* AnimationObject ; 
		vector<SpriteObject*> PausedObj ; 
		float lifespan; 
	};
	private:
		vector<AnimatorObj*> spriteObjectDict;
 
	public :
		AnimatorManager() {

		}

		//Responsible to "hide" (not replace) object(s) and spawn animationObj in their position with some given adjustment 
		void CreateAnimationFactory(vector<SpriteObject*> objToHide, glm::vec3 pos, glm::vec3 size, float _lifespan  , string fileName, int row, int column
			, int howManyFrame, int delayBetaweenFrame) {
			
			AnimatorObj* anim = new AnimatorObj();
			anim->lifespan = _lifespan;

			anim->AnimationObject = new SpriteObject(fileName,row,column,pos,size);
			anim->AnimationObject->SetAnimationLoop(0, 0, howManyFrame, delayBetaweenFrame, true);

			for (SpriteObject* s : objToHide) {
				anim->PausedObj.push_back(s);
				s->SetPause(true);
			}


			
			spriteObjectDict.push_back(anim);


			return;
		}

 
		void Update(int deltaTime){
			for (int i = 0; i < spriteObjectDict.size(); i ++) {
				AnimatorObj* spriteObject = spriteObjectDict[i];
				spriteObject->lifespan -= 1.0f / 1000 * GameEngine::GetInstance()->GetDeltaTime(); 
				cout << spriteObject->lifespan << endl;
 				if (spriteObject->lifespan <= 0) {
					delete spriteObject->AnimationObject ;
					 
					for (int k = 0; k < spriteObject->PausedObj.size(); k++) {
						spriteObject->PausedObj[k]->SetPause(false);
					}

					spriteObjectDict.erase(spriteObjectDict.begin() + i);
				}
			}
 
		}
};

