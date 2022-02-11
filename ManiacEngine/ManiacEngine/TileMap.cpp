#include "TileMap.h"

void TileMap::SetUV(float widthEachCell , float heightEachCell, int columnMax, int rowMax,int i,int j,int** Mapdata,
	float uvs[8]) {
	int data = Mapdata[i][j]; 
 
  	int currentColumn = data % columnMax;
	int r = floor(data / (float)columnMax) >= 0 ? floor(data / (float)columnMax) : 0 ;
	int currentRow =   r ;

	uvs[0] = currentColumn / (columnMax * 1.0f)  ;
	uvs[1] = currentRow  / (rowMax * 1.0f)   ;
 
	uvs[2] = (currentColumn + 1) / (columnMax * 1.0f)  ;
	uvs[3] = currentRow  / (rowMax * 1.0f)  ;

	uvs[4] = (currentColumn + 1) / (columnMax * 1.0f) ;
	uvs[5] = (currentRow   + 1 ) / (rowMax * 1.0f)  ;

	uvs[6] = currentColumn / (columnMax * 1.0f)  ;
	uvs[7] = (currentRow   + 1) / (rowMax * 1.0f)  ;

 }

 

TileMap::TileMap(int width, int height, int** Mapdata_Front_Layer , int** Mapdata_Middle_Layer,int** Mapdata_Back_Layer, int **ColMapdata, string texture_path, int rowMax, int columnMax) {
	this->Map_Height = height; 
	this->Map_Width = width; 
	width -= 1;
	height -= 1;

	unsigned int texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(texture_path);

	/// Create Background Layer 
	for (int i = 0; i < width + 1; i++) {
		tiles.push_back(vector<SpriteObject*>());
		for (int j = 0; j < height + 1; j++) {
			/// Create every tile 
			tiles[i].push_back(new SpriteObject(texture, rowMax, columnMax, glm::vec3((-GameEngine::GetInstance()->GetWindowWidth() / 2 + j * 63 + 33), GameEngine::GetInstance()->GetWindowHeight() / 2 - (i) * 63 - 33, 0)
				,glm::vec3(64,-64,1)));

			tiles[i][j]->SetAnimationLoop(0, 0, 0, 0, false);

			/// Set Size of each tile to 64 pixle width and height  
 
			/// Set position of each tile 
 			if (Mapdata_Back_Layer[i][j] == -1) tiles[i][j]->SetPosition(glm::vec3(width * 10000, height * 10000, 0));

			/// Calculate UV 
			float uvs[8];

 
			//Need to use Mapdata[i][j] for UV 
			float widthEachCell = 1.0f / (float)columnMax;
			float heightEachCell = 1.0f / (float)rowMax;
			SetUV(widthEachCell, heightEachCell, columnMax, rowMax, i, j,
				Mapdata_Back_Layer, uvs);

			tiles[i][j]->SetUV(uvs);

		}
	}

	/// Create tile in Middle Layer 
	for (int i = 0; i < width + 1; i++) {
		tiles.push_back(vector<SpriteObject*>());
		for (int j = 0; j < height + 1; j++) {
			/// Create every tile
			tiles[i + width + 1].push_back(new SpriteObject(texture, rowMax, columnMax, glm::vec3((-GameEngine::GetInstance()->GetWindowWidth() / 2 + j * 63 + 33), GameEngine::GetInstance()->GetWindowHeight() / 2 - (i) * 63 - 33, 0)
				, glm::vec3(64, -64, 1)));

			tiles[i + width + 1][j]->SetAnimationLoop(0, 0, 0, 0, false);


			/// Set position of each tile
 
 			if (Mapdata_Middle_Layer[i][j] == -1)tiles[i + width + 1][j]->SetPosition(glm::vec3(width * 10000, height * 10000, 0));

			/// Calculate UV
			float uvs[8];

			//Need to use Mapdata[i][j] for UV
			float widthEachCell = 1.0f / (float)columnMax;
			float heightEachCell = 1.0f / (float)rowMax;

			SetUV(widthEachCell, heightEachCell, columnMax, rowMax, i, j,
				Mapdata_Middle_Layer, uvs);
			tiles[i + width + 1][j]->SetUV(uvs);
		}
	}
	/// Create tile in Front Layer
	/*for (int i = 0; i <  width + 1   ; i++) {
		tiles.push_back(vector<SpriteObject*>());
		for (int j = 0; j < height + 1; j++) {
			/// Create every tile
			tiles[i + width + 1 + width].push_back(new SpriteObject(texture, rowMax, columnMax, glm::vec3((-GameEngine::GetInstance()->GetWindowWidth() / 2 + j * 64 + 32), GameEngine::GetInstance()->GetWindowHeight() / 2 - (i) * 64 - 32, 0)
				, glm::vec3(64, -64, 1)));
			tiles[i + width + 1 + width ][j]->SetAnimationLoop(0, 0, 0, 0,false);

			/// Set position of each tile
 			if (Mapdata_Front_Layer[i][j] == -1)tiles[i + width  + width + 1][j]->SetPosition(glm::vec3(width * 10000, height * 10000, 0));

			/// Calculate UV
			float uvs[8];

			//Need to use Mapdata[i][j] for UV
			float widthEachCell = 1.0f / (float)columnMax;
			float heightEachCell = 1.0f / (float)rowMax;

			SetUV(widthEachCell, heightEachCell, columnMax, rowMax, i, j,
				Mapdata_Front_Layer, uvs);
			tiles[i + width + width + 1][j]->SetUV(uvs);
		}
	}*/

	/// Create all collision object for every tiles. 
	for (int i = 0; i < width + 1; i++) {
		for (int j = 0; j < height + 1; j++) {
			if (ColMapdata[i][j] == 1) {
				InvisibleObject* newInv = new InvisibleObject();
				newInv->SetPosition(glm::vec3(-GameEngine::GetInstance()->GetWindowWidth() / 2 + j * 63 + 33, GameEngine::GetInstance()->GetWindowHeight() / 2 - (i) * 63 - 33, 1));
				newInv->SetSize(64, 64);
				newInv->SetRender(true);
				tiles_collision.push_back(newInv);
				 
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

vector<InvisibleObject*> TileMap::GetColTiles() {
	return tiles_collision; 
}

 