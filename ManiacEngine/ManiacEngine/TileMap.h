#ifndef TILEMAP
#define TILEMAP
#include "SpriteObject.h"
#include "GameEngine.h"


class TileMap  {
	private : 
 		vector<vector<SpriteObject*>> tiles;
	public : 
		TileMap(int width, int height, int** Mapdata, string texture_path, int rowMax, int columnMax); 
		~TileMap(); 

		vector<vector<SpriteObject*>> GetTiles(); 
		
 };

#endif 