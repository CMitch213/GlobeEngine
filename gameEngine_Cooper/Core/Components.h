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