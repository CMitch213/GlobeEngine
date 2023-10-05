#pragma once
#include "ECS.h"
#include "Engine.h"

struct Transform
{

public:
	ECS_DECLARE_TYPE;
	float xPos;
	float yPos;
	float rotation;

	Transform(float newX, float newY): xPos(newX), yPos(newY), rotation(0.0f) {
		
	}
};
ECS_DEFINE_TYPE(Transform);

struct Sprite2D {
public:
	ECS_DECLARE_TYPE;
	sf::Sprite picture;
	std::string texturePath;
	int width, height;

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