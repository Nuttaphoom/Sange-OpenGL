#pragma once
#include "GameEngine.h"
#include "InvisibleObject.h"


class TileMap  {
	private : 
 		vector<vector<SpriteObject*>> tiles ;
		vector<InvisibleObject*> tiles_collision ; 
		int Map_Width, Map_Height; 
	public : 
		TileMap(int width, int height,int** FrontMiddleMapData ,int** MiddleMapdata,int** BackGroundMapDat, int** ColMapdata, string texture_path, int rowMax, int columnMax);
		~TileMap(); 
		void SetUV(float widthEachCell, float heightEachCell, int columnMax, int rowMax, int i, int j, int** Mapdata,float uvs[8]);
		vector<vector<SpriteObject*>> GetTiles(); 
		vector<InvisibleObject*> GetColTiles();
		

  };

