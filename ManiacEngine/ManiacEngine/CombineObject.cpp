
#include "CombineObject.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "TriangleMeshVbo.h"


CombineObject::CombineObject()
{
	color = glm::vec3(0.0, 0.0, 0.0);
}


CombineObject::~CombineObject()
{
}

void CombineObject::SetColor(float r, float g, float b)
{
	color = glm::vec3(r, g, b);
}

void CombineObject::SetColor2(float r, float g, float b)
{
	color2 = glm::vec3(r, g, b);
}

void CombineObject::Render(glm::mat4 globalModelTransform)
{
	SquareMeshVbo *squareMesh = dynamic_cast<SquareMeshVbo *> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));
	TriangleMeshVbo * triangleMesh = dynamic_cast<TriangleMeshVbo *> (GameEngine::GetInstance()->GetRenderer()->GetMesh(TriangleMeshVbo::MESH_NAME));

	GLuint modelMatixId = GameEngine::GetInstance()->GetRenderer()->GetModelMatrixAttrId();
	GLuint colorId = GameEngine::GetInstance()->GetRenderer()->GetColorUniformId();


	if (modelMatixId == -1) {
		cout << "Error: Can't perform transformation " << endl;
		return;
	}
	if (colorId == -1) {
		cout << "Error: Can't set color " << endl;
		return;
	}
	vector <glm::mat4> matrixStack;

	glm::mat4 currentMatrix = this->getTransform();

	if (squareMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform3f(colorId, color.x, color.y, color.z);
		squareMesh->Render();

	}

	if (triangleMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform3f(colorId, color2.x, color2.y, color2.z);
		triangleMesh->Render();

	}
}

