#include "TileMap.h"

void SetUV(float widthEachCell , float heightEachCell, int width, int height,int i,int j,int** Mapdata,
	float uvs[8]) {
	uvs[0] = widthEachCell * Mapdata[i][j];
	uvs[1] = (height - (Mapdata[i][j] / width)) * (heightEachCell)-1;

	uvs[2] = (widthEachCell * Mapdata[i][j]) + widthEachCell;
	uvs[3] = (height - (Mapdata[i][j] / width)) * (heightEachCell)-1;

	uvs[4] = (widthEachCell * Mapdata[i][j]) + widthEachCell;
	uvs[5] = (height - (Mapdata[i][j] / width)) * (heightEachCell);

	uvs[6] = (widthEachCell * Mapdata[i][j]);
	uvs[7] = (height - (Mapdata[i][j] / width)) * (heightEachCell); 
	return;
}

TileMap::TileMap(int width, int height, int** Mapdata_Front_Layer , int** Mapdata_Middle_Layer,int **ColMapdata, string texture_path, int rowMax, int columnMax) {
	this->Map_Height = height; 
	this->Map_Width = width; 
	width -= 1;
	height -= 1;
	unsigned int texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(texture_path);


	/// Create tile in Middle Layer 
	for (int i = 0; i <  width + 1   ; i++) {
		tiles.push_back(vector<SpriteObject*>());

		for (int j = 0; j < height + 1; j++) {
			/// Create every tile 
			tiles[i].push_back(new SpriteObject(texture, rowMax, columnMax));
			if (Mapdata_Middle_Layer[i][j] != -1)
			{
				tiles[i][j]->SetAnimationLoop(0, 0, 0, 0);

				/// Set Size of each tile to 64 pixle width and height  
				tiles[i][j]->SetSize(64, -64);

				/// Set position of each tile 
				tiles[i][j]->SetPosition(glm::vec3(-GameEngine::GetInstance()->GetWindowWidth() / 2 + j * 64 + 32, GameEngine::GetInstance()->GetWindowHeight() / 2 - (i) * 64 - 32, 1));
				/// Calculate UV 
				float uvs[8];

				//Need to use Mapdata[i][j] for UV // UNFINISH !!!
				float widthEachCell = 1.0f / (float)width;
				float heightEachCell = 1.0f / (float)height;

				SetUV(widthEachCell, heightEachCell, width, height, i, j,
					Mapdata_Middle_Layer, uvs);

				tiles[i][j]->SetUV(uvs);
			}
		}
	}

	/// Create tile in Middle Layer 
	for (int i = 0; i < width + 1; i++) {
		tiles.push_back(vector<SpriteObject*>());

		for (int j = 0; j < height + 1; j++) {
			/// Create every tile 
			tiles[i + width + 1].push_back(new SpriteObject(texture, rowMax, columnMax));
			if (Mapdata_Front_Layer[i][j] != -1) {

				tiles[i + width + 1][j]->SetAnimationLoop(0, 0, 0, 0);

				/// Set Size of each tile to 64 pixle width and height  
				tiles[i + width + 1][j]->SetSize(64, -64);

				/// Set position of each tile 
				tiles[i + width + 1][j]->SetPosition(glm::vec3(-GameEngine::GetInstance()->GetWindowWidth() / 2 + j * 64 + 32, GameEngine::GetInstance()->GetWindowHeight() / 2 - (i) * 64 - 32, 1));
				/// Calculate UV 
				float uvs[8];

				//Need to use Mapdata[i][j] for UV // UNFINISH !!!
				float widthEachCell = 1.0f / (float)width;
				float heightEachCell = 1.0f / (float)height;

				SetUV(widthEachCell, heightEachCell, width, height, i, j,
					Mapdata_Front_Layer, uvs);

				tiles[i + width + 1][j]->SetUV(uvs);
			}
		}
	}

	for (int i = 0; i < width + 1; i++) {
		tiles_collision.push_back(vector<InvisibleObject*>());
		for (int j = 0; j < height + 1; j++) {
			/// Create all collision object for every tiles. 
			if (ColMapdata[i][j] == 1) {
				tiles_collision[i].push_back(new InvisibleObject());
				tiles_collision[i][j]->SetPosition(glm::vec3(-GameEngine::GetInstance()->GetWindowWidth() / 2 + j * 64 + 32, GameEngine::GetInstance()->GetWindowHeight() / 2 - i * 64 - 32, 1));
				tiles_collision[i][j]->SetSize(64, -64);
				tiles_collision[i][j]->SetRender(true);
			}
		}
	}
}

TileMap::~TileMap() {
	for (int i = 0; i < tiles.size(); i++) {
		for (int j = 0; j < tiles[i].size(); j++) {
			delete tiles[i][j];
		}
	}
}

vector<vector<SpriteObject*>> TileMap::GetTiles() {
	return tiles;
}

vector<vector<InvisibleObject*>> TileMap::GetColTiles() {
	return tiles_collision; 
}