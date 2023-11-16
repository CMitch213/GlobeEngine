#include "TileMapSystem.h"
#include "../Utils/States.h"
#include "../GUI/ButtonMap.h"

void TileMapSystem::tick(ECS::World* world, float deltaTime)
{
	const std::string& fileName = "tileTest.txt";
	world->each<TileMap>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<TileMap> tileMap)-> void {
				if (!States::GetPausedState()) {
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						AddTileOnClick(true, tileMap);
						std::cout << "Entity ID: " << entity->getEntityId() << "(With Collision)\n";
					}
					else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
						AddTileOnClick(false, tileMap);
						std::cout << "Entity ID: " << entity->getEntityId() << "(Without Collision)\n";
					}
				}

				if (ButtonMap::GetMap()["SAVE"]->bClicked) {
					std::cout << "Saved TileMap\n";
					tileMap->SaveTileMap(fileName);
					ButtonMap::GetMap()["SAVE"]->bClicked = false;
				}

				if (ButtonMap::GetMap()["LOAD"]->bClicked) {
					std::cout << "Loaded TileMap\n";
					tileMap->LoadTileMap(fileName);
					ButtonMap::GetMap()["LOAD"]->bClicked = false;
				}
		});
}

void TileMapSystem::AddTileOnClick(bool bHasCollision, ECS::ComponentHandle<TileMap> tileMap)const
{
	//References to window to determine active cursors position for adding tiles
	const sf::RenderWindow* winRef = Engine::GetInstance().window;
	const sf::Vector2f mousePosView = winRef->mapPixelToCoords(sf::Mouse::getPosition(*winRef));
	const sf::Vector2i mousePosGrid(
		static_cast<int32_t>(mousePosView.x / tileMap->gridSizeF),
		static_cast<int32_t>(mousePosView.y / tileMap->gridSizeF));
	tileMap->AddTile(mousePosGrid.x, mousePosGrid.y, 0, bHasCollision);
	
}
