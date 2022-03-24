#include "HandleKey.h"
#include "PlayerHandleKey.h"

void HandleKey::KeyDetect(char key) {
	PlayerHandleKey i;
	switch (key)
	{
		case 'w':
			i.PlayerStateCheck(key);
			break;
		case 's':
			i.PlayerStateCheck(key);
			break;
		case 'a':
			i.PlayerStateCheck(key);
			break;
		case 'd':
			i.PlayerStateCheck(key);
			break;
		case 'e':
			i.PlayerStateCheck(key);
			break;
	}
}