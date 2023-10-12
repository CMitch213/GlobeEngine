#pragma once
#include "ECS.h"
#include "Engine.h"

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
		xSpeed(xPos), ySpeed(yPos),
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