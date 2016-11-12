//! @file TileMap.h
//! @brief Header file for TileMap Class
//!
//! Libraries used:
//! SMFL: The library was used to so that we can have a GUI for displaying maps.
//! It was the easiest library to use out of the ones we researched.
//! Standard Input/Output Streams Library <iostream> is necessary to display the stats of the character created, by using cout
//! Statndard vector library was used so to facillitate dynamic arrays.
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
	void setMap(sf::Vector2u tileSize, std::vector<int>& tiles, unsigned int width, unsigned int height);
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

