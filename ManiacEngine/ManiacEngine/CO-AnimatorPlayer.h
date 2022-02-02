#pragma once
#include "Entity.h"

class CoAnimatorPlayer {
	private : 
		Entity enOne;
		Entity enTwo; 

		float animationTime; 
		float curAnimationTime;   

	public : 
		void PlayAnimation(Entity A, Entity B,int startRowA,int startColA, int howManyFrameA, int delayBetweenFrameA, int startRowB,int startColB,int howManyFrameB,int delayBetweenFrameB,float animationTime) {
			curAnimationTime = 0; 
			this->animationTime = animationTime;
			A.SetAnimationLoop(startRowA, startColA, howManyFrameA, delayBetweenFrameA);  
			B.SetAnimationLoop(startRowB, startColB, howManyFrameB, delayBetweenFrameB);

			
		}

		void Update() {
			if (curAnimationTime >= animationTime) {

			}
		}


};
 