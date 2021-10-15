#ifndef TILEMAP
#define TILEMAP
#include "SpriteObject.h"
#include "GameEngine.h"


class TileMap  {
	private : 
 		vector<vector<SpriteObject*>> tiles;
	public : 
		TileMap(int width, int height ,int** Mapdata, string texture_path, int rowMax, int columnMax) {
			width -= 1;
			height -= 1; 

			for (int i = 0; i < width + 1; i++) {
				tiles.push_back(vector<SpriteObject*>());
				for (int j = 0; j < height + 1; j++) {
 					tiles[i].push_back(new SpriteObject(texture_path, rowMax, columnMax));
					
					tiles[i][j]->SetAnimationLoop(0, 0, 0, 0);

					/// Set Size of each tile to 64 pixle width and height  
					tiles[i][j]->SetSize(64, -64);

 					/// Set position of each tile 
					tiles[i][j]->SetPosition(glm::vec3(-GameEngine::GetInstance()->GetWindowWidth() / 2 + j * 64 + 32 , GameEngine::GetInstance()->GetWindowHeight() / 2 - i * 64 - 32, 1));
 					/// Calculate UV 
					float uvs[8] ; 
 					
					//Need to use Mapdata[i][j] for UV // UNFINISH !!!
					float widthEachCell = 1.0f / (float)   width  ;
					float heightEachCell = 1.0f / (float)  height   ;

					cout << "widthEachCell : " << widthEachCell << endl;

					uvs[0] = widthEachCell * Mapdata[i][j];		
					uvs[1] = (height - ( Mapdata[i][j] / width)) * (heightEachCell) - 1 ;

					uvs[2] = (widthEachCell * Mapdata[i][j]) + widthEachCell;
					uvs[3] = (height - (Mapdata[i][j] / width)) * (heightEachCell)-1;

					uvs[4] = (widthEachCell * Mapdata[i][j]) + widthEachCell;
					uvs[5] = (height - (Mapdata[i][j] / width)) * (heightEachCell) ;

					uvs[6] = (widthEachCell * Mapdata[i][j])  ;
					uvs[7] = (height - (Mapdata[i][j] / width)) * (heightEachCell) ;
					
					cout << uvs[6] << "," << uvs[7] << "\t" << uvs[4] << "," << uvs[5] << endl;
					cout << uvs[0] << "," << uvs[1] << "\t" << uvs[2] << "," << uvs[3] << endl;
					cout << endl << endl << endl;

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