#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
class ImageObject :public virtual DrawableObject
{
	unsigned int texture;

public:
	ImageObject();
	~ImageObject();
	void SetTexture(string path);
	unsigned int GetTexture();
	void Render(glm::mat4 globalModelTransform);
};
