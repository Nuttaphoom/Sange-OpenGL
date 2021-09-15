#ifndef CAMMERACLASS
#define CAMMERACLASS

#include "GLRenderer.h"
using namespace std;

class Camera {
private:
	static Camera* instance;
	glm::vec3 CamOffset;
public:
	Camera();
	static Camera* GetInstance();
	glm::vec3 GetCamOffset();
	void Translate(float x, float y);
};


#endif 