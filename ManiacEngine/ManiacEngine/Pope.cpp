#include "Pope.h"


Pope::Pope(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size) :Enemy(fileName, row, column, 100, 80.0f, Pos, Size, glm::vec3(Size.x / 2, Size.y, 0)) {
 	ChangeState(StateMachine::IDLE);
}

Pope::Pope(unsigned int texture, int row, int column, glm::vec3 Pos, glm::vec3 Size): Enemy(texture, row, column, 100, 80.0f, Pos, Size, glm::vec3(Size.x / 2, Size.y, 0)) {
    ChangeState(StateMachine::IDLE);
}

void Pope::Update(int deltaTime) {
    Entity::Update(deltaTime);

    if (IsPause())
        return;

    
    UpdateStateMachine(deltaTime);
}

//Only Idle and Walking
void Pope::UpdateStateMachine(float deltatime) {

}

void Pope::ChangeState(StateMachine nextState) {

}

StateMachine Pope::GetState() {
    return _popeState;
}

void Pope::AddPatrolPos(glm::vec3 pos) {

}

void Pope::Patrol() {

}

bool Pope::PlayerDetect(Entity* p) {
    return false;
}

void  Pope::PlayerChase(Entity* p) {

}

void  Pope::Render(glm::mat4 globalModelTransform) {

}