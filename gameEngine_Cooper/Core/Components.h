#pragma once
#include "ECS.h"
#include "Engine.h"
#include "../Utils/Tile.h"
#include <fstream>

struct Transform
{

public:
	ECS_DECLARE_TYPE;

	sf::Vector2f position;
	sf::Vector2f speed;
	float rotationAngle, rotationSpeed;
	bool bCollide;

	Transform(sf::Vector2f position, sf::Vector2f speed, float rotationAngle = 0.0f, float rotationSpeed = 0.0f) :
		position(position.x, position.y),
		speed(speed.x, speed.y),
		rotationAngle(rotationAngle), rotationSpeed(rotationSpeed),
		bCollide(false)
	{}

	void Move()
	{
		if (bCollide == false)
		{
			this->position += this->speed;
		}
	}
	
	void Normalize(const sf::Vector2f speed) {
		const auto magnitude = static_cast<float>(sqrt(speed.x * speed.x + speed.y * speed.y));

		this->speed.x = speed.x / magnitude;
		this->speed.y = speed.y / magnitude;
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
	bool bInputActive, 
		wKey, aKey, sKey, dKey, spaceKey;

	InputController() : bInputActive(true),
		wKey(false), aKey(false), sKey(false), dKey(false), spaceKey(false) {

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

struct RectangleCollider {

public:
	ECS_DECLARE_TYPE;
	sf::RectangleShape shape;
	float left;
	float right;
	float top;
	float bottom;
	float gridSizeF;

	RectangleCollider() 
		: left(0.0f), right(0.0f), top(0.0f), bottom(0.0f), gridSizeF(50.0f)
	{
		shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
		shape.setPosition(left * gridSizeF, top * gridSizeF);

		//Uncomment to see hitbox
		//shape.setFillColor(sf::Color::Cyan);
	}

	void Update(float x, float y, const float gridSizeF) {
		this->left = x;
		this->right = x + gridSizeF;
		this->top = y;
		this->bottom = y + gridSizeF;
		this->gridSizeF = gridSizeF;
	}
};
ECS_DEFINE_TYPE(RectangleCollider);

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
		if (x < this->maxSize.x && x >= 0u &&
			y < this->maxSize.y && y >= 0u &&
			z < this->layers && z >= 0u)
		{
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

struct Tag {
	ECS_DECLARE_TYPE;

public:
	std::vector<std::string> tagNames;
	Tag() = default;
	~Tag() = default;

	void AddTag(const std::string& tag) {
		tagNames.emplace_back(tag); /*Adds to array*/
	}

	bool ContainsTag(const std::string& tag) {
		return std::find(tagNames.begin(), tagNames.end(), tag) != tagNames.end();
	}
}
ECS_DEFINE_TYPE(Tag);