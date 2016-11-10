#pragma once
#include "SFML\Graphics.hpp"
#include <vector>
class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	TileMap();
	~TileMap();
	bool load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int>& tiles, unsigned int width, unsigned int height);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

