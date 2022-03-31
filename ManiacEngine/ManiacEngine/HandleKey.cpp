#include "HandleKey.h"
#include "PlayerHandleKey.h"

void HandleKey::KeyDetect(char key) {
	PlayerHandleKey i;

	i.PlayerStateCheck(key);
}