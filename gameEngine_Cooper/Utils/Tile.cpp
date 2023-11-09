#include "Tile.h"

Tile::Tile(float xPos, float yPos, float gridSizeF, bool bColliding) : bColliding(bColliding)
{
    shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(xPos * gridSizeF, yPos * gridSizeF);
}

void Tile::Render(sf::RenderTarget& target) const
{
    target.draw(shape);
}

const bool& Tile::GetCollision() const
{
    return bColliding;
}

const sf::Vector2f& Tile::GetPosition() const
{
    return shape.getPosition();
}

std::string Tile::ToString() const
{
    std::stringstream stringForm;
    stringForm << bColliding << " ";
    return stringForm.str();
}
