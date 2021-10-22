#ifndef TILEMAP
#define TILEMAP
#include "SpriteObject.h"
#include "GameEngine.h"
#include "InvisibleObject.h"


class TileMap  {
	private : 
 		vector<vector<SpriteObject*>> tiles ;
		vector<vector<InvisibleObject*>> tiles_collision ; 
	public : 
		TileMap(int width, int height, int** Mapdata, int** ColMapdata, string texture_path, int rowMax, int columnMax);
		~TileMap(); 
 
		vector<vector<SpriteObject*>> GetTiles(); 
		vector<vector<InvisibleObject*>> GetColTiles();
		
 };

#endif 