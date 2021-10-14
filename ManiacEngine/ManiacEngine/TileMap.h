#ifndef TILEMAP
#define TILEMAP
#include "SpriteObject.h"
#include "GameEngine.h"


class TileMap  {
	private : 
 		vector<vector<SpriteObject*>> tiles;
	public : 
		TileMap(int width, int height ,int** Mapdata, string texture_path, int rowMax, int columnMax) {
			for (int i = 0; i < width; i++) {
				tiles.push_back(vector<SpriteObject*>());
				for (int j = 0; j < height; j++) {
					std::cout << "get here " << i << " , " << j << std::endl; 
					tiles[i].push_back(new SpriteObject(texture_path, rowMax, columnMax));
					
					tiles[i][j]->SetAnimationLoop(0, 0, 0, 0);

					/// Set Size of each tile to 64 pixle width and height  
					tiles[i][j]->SetSize(64, -64);

 					/// Set position of each tile 
					tiles[i][j]->SetPosition(glm::vec3(-GameEngine::GetInstance()->GetWindowWidth() / 2 + i * 64 + 32 , GameEngine::GetInstance()->GetWindowHeight() / 2 - j * 64 - 32, 1));
 					/// Calculate UV 
					float uvs[8] ; 
 					
					//Need to use Mapdata[i][j] for UV // UNFINISH !!!
					uvs[0] = (	(1 / width) ) ;
					uvs[1] = (	(1 / height) * (height - Mapdata[i][j])	);
					
					uvs[2] = (	(1 / width) * Mapdata[i][j]) + 1 / width;
					uvs[3] = (	(1 / height) * (height - Mapdata[i][j])	);

					uvs[4] = (	(1 / width) * Mapdata[i][j]) + 1 / width;
					uvs[5] = (	(1 / height) * (height - Mapdata[i][j]) + 1 / height);

					uvs[6] = (	(1 / width) * Mapdata[i][j]);
					uvs[7] = (	(1 / height) * (height - Mapdata[i][j]) + 1 / height);

					tiles[i][j]->SetUV(uvs);
				}
			}
		}

		~TileMap() {
			for (int i = 0; i < tiles.size(); i++) {
				for (int j = 0; j < tiles[i].size();  j++) {
					delete tiles[i][j]; 
				}
			}
		}

		vector<vector<SpriteObject*>> GetTiles () {
			return tiles; 
		}
		
 };

#endif 