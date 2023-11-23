#pragma once
#include "ECS.h"
#include "Engine.h"
#include "../Utils/Tile.h"
#include <fstream>

struct Transform
{

public:
	ECS_DECLARE_TYPE;
	float xPos, yPos;
	float rotationAngle;
	float rotationSpeed;
	float xSpeed, ySpeed;
	float xSpeedMod, ySpeedMod;

	bool bCollide;

	Transform(float newX, float newY, float xSpeed = 0.0f, float ySpeed = 0.0f, float rotationAngle = 0.0f, float rotationSpeed = 0.0f): 
		xPos(newX), yPos(newY), 
		xSpeed(xSpeed), ySpeed(ySpeed),
		xSpeedMod(xSpeed), ySpeedMod(ySpeed),
		rotationAngle(rotationAngle), rotationSpeed(rotationSpeed),
		bCollide(false){
		//Start of constructor

	}

	void Move(){
		if (bCollide == false)
		{
			this->xPos += xSpeed;
			this->yPos += ySpeed;
		}
	}
};
ECS_DEFINE_TYPE(Transform);

struct Sprite2D {
public:
	ECS_DECLARE_TYPE;
	sf::Sprite picture;
	std::string texturePath;
	float width, height;

	Sprite2D(std::string filePath): texturePath(filePath) {

	}
};
ECS_DEFINE_TYPE(Sprite2D);

struct Animator {
public:
	ECS_DECLARE_TYPE;
	int spriteWidth, spriteHeight;
	int currentColumn, currentRow;
	int totalColumns, totalRows;

	float currentTime, nextFrameTime;
	bool bFacingRight;

	Animator(int newWidth, int newHeight, int columns, int rows, float timeBetweenFrames) : 
		//Initialize all the stuff made above
		spriteWidth(newWidth), spriteHeight(newHeight), 
		currentColumn(0), currentRow(0), totalColumns(columns), totalRows(rows), 
		currentTime(0), nextFrameTime(timeBetweenFrames), 
		bFacingRight(true)
	{

	}
};
ECS_DEFINE_TYPE(Animator);

struct InputController {

public:
	ECS_DECLARE_TYPE;
	bool bInputActive, wKey, aKey, sKey, dKey;

	InputController() : bInputActive(true), wKey(false), aKey(false), sKey(false), dKey(false) {

	}

};
ECS_DEFINE_TYPE(InputController);

struct BoxCollider {

public:
	ECS_DECLARE_TYPE;
	float leftEdge, rightEdge, topEdge, bottomEdge;

	BoxCollider() : leftEdge(0.0f), rightEdge(0.0f), topEdge(0.0f), bottomEdge(0.0f) {

	}

	void Update(float x, float y, float width, float height) {
		this->leftEdge = x;
		this->rightEdge = x + width;
		this->topEdge = y;
		this->bottomEdge = y + height;
	}
};
ECS_DEFINE_TYPE(BoxCollider);

struct TileMap {

public:
	ECS_DECLARE_TYPE;
	float gridSizeF;
	uint32_t gridSizeU;
	uint32_t layers;
	sf::Vector2u maxSize;
	sf::RectangleShape collisionBox;
	std::vector<std::vector<std::vector<Tile*>>> map;
	TileMap() : gridSizeF(50.0f), 
		/*Making gridSizeU = gridSizeF*/ gridSizeU(static_cast<uint32_t>(gridSizeF)), 
		layers(1),
		maxSize(sf::Vector2u(20, 20))
	{
		map.resize(maxSize.x);
		for (size_t x = 0; x < maxSize.x; x++)
		{
			//Push_Back = add
			map.push_back(std::vector<std::vector<Tile*>>());

			for (size_t y = 0; y < maxSize.y; y++)
			{
				map.at(x).resize(maxSize.y);
				map.at(x).push_back(std::vector<Tile*>());

				for (size_t z = 0; z < layers; z++)
				{
					map.at(x).at(y).resize(layers);
					map.at(x).at(y).push_back(nullptr);
				}
			}
		}

		collisionBox.setSize(sf::Vector2f(gridSizeF, gridSizeF));
		collisionBox.setFillColor(sf::Color(150, 255, 69, 50));
		collisionBox.setOutlineColor(sf::Color::Green);
		collisionBox.setOutlineThickness(-0.5f);
	}

	~TileMap() {
		Clear();
	}

	void Clear() {
		for (size_t x = 0; x < maxSize.x; x++)
		{
			for (size_t y = 0; y < maxSize.y; y++) 
			{
				for (size_t z = 0; z < layers; z++) 
				{
					delete map.at(x).at(y).at(z);
				}

				map.at(x).at(y).clear();
			}
			map.at(x).clear();
		}
		map.clear();
	}

	void AddTile(const int32_t x, const int32_t y, const int32_t z, bool bHasCollision) {
		//Make sure tiles are being placed on the grid
		if (x >= 0 && y >= 0 && z >= 0) 
		{
			//Check if a tile is not already in use	
			if (map.at(x).at(y).at(z) == nullptr) {
				//Create A Tile
				map.at(x).at(y).at(z) = new Tile(static_cast<float>(x), static_cast<float>(y), gridSizeF, bHasCollision);
				std::cout << "Added Tile" << std::endl;
			}
		}
	}

	void SaveTileMap(const std::string& fileName)const {
		std::ofstream saveFile;
		saveFile.open(fileName);
		if (saveFile.is_open()) {
			//Gather Level Info
			saveFile << maxSize.x << " " << maxSize.y << "\n"
				<< gridSizeF << "\n"
				<< layers << "\n";
			//Gets all the tiles that are placed by the user
			for (size_t x = 0; x < maxSize.x; x++) {
				for (size_t y = 0; y < maxSize.y; y++){
					for (size_t z = 0; z < layers; z++)
					{
						if (this->map[x][y][z] != nullptr)
						{
							//Saves Level Info to a Text File
							saveFile << x << " " << y << " " << z << " " << map.at(x).at(y).at(z)->ToString() << "\n";
						}
					}
				}
			}
		}
		else {
			//Cant Save File
			std::cerr << "Error 404: TileMap Could Not Be Saved To File " << fileName << std::endl;
		}

		saveFile.close();
	}

	void LoadTileMap(const std::string& fileName) {
		std::ifstream loadFile;
		loadFile.open(fileName);
		if (loadFile.is_open()) {
			bool bColliding = false;
			//Reads the position of all tiles previously saved from a text file
			loadFile >> maxSize.x >> maxSize.y >> gridSizeF >> layers;
			//Remove unsaved tiles
			Clear();
			map.resize(maxSize.x, std::vector<std::vector<Tile* >>());
			//Get all the tiles from save file
			for (size_t x = 0; x < maxSize.x; x++) {
				for (size_t y = 0; y < maxSize.y; y++) {
					map.at(x).resize(maxSize.y, std::vector<Tile* >());
					for (size_t z = 0; z < layers; z++) {
						map.at(x).at(y).resize(layers, nullptr);
					}
				}
			}
			//While reading the tile data from text file.
			while (loadFile >> maxSize.x >> maxSize.y >> layers >> bColliding) {
				std::cout << maxSize.x << ", "
					<< maxSize.y << ", "
					<< layers << ", "
					<< std::endl;
				//Restore / Adds Tiles from saved text file
				map.at(maxSize.x).at(maxSize.y).at(layers) = new Tile(static_cast<float>(maxSize.x), static_cast<float>(maxSize.y), gridSizeF, bColliding);
			}
		}
		else {
			//Cant Load File
			std::cerr << "Error 404: TileMap Could Not Be Load File " << fileName << std::endl;
		}
		loadFile.close();
	}
};
ECS_DEFINE_TYPE(TileMap);