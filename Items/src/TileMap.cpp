/*@file TileMap.cpp
* @brief Implementation file for the Chest .cpp file
*/
#include "TileMap.h"
#include "TileTypes.h"


//! TileMap default constructor
//! @brief does nothing.
TileMap::TileMap()
{
}

//! TileMap default destructor
//! @brief does nothing.
TileMap::~TileMap()
{
}

//! load function
//! @brief loads tiles from sprite sheet
//! @param tilset, tile set to load.
//! @param tileSize the size of each tile in  the sheet.
//! @param vector of the tile numbers.
//! @width # of tiles per row
//! @height # of tiles per column
bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int>& tiles, unsigned int width, unsigned int height)
{
	//Load the tileset texture
	if (!m_tileset.loadFromFile("bkrd.png"))
	{
		return false;
	}

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width*height * 4);

	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{
			//get the current tile number (1d array)
			int tileNumber = tiles[i + j*width];

			//find its position in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

			//get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j*width) * 4];

			//Define its 4 corners
			quad[0].position = sf::Vector2f(i*tileSize.x, j*tileSize.y);
			quad[1].position = sf::Vector2f((i + 1)*tileSize.x, j*tileSize.y);
			quad[2].position = sf::Vector2f((i + 1)*tileSize.x, (j + 1)*tileSize.y);
			quad[3].position = sf::Vector2f(i*tileSize.x, (j + 1)*tileSize.y);

			//Define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu*tileSize.x, tv*tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1)*tileSize.x, tv*tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1)*tileSize.x, (tv + 1)*tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu*tileSize.x, (tv + 1)*tileSize.y);
		}
	return true;
}

//! draw function
//! @brief draws the tiles.
//! @param target the window to draw the tilemap to
//! @param the state of the window.
void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//apply the transform
	states.transform *= getTransform();
	//apply the tileset texture
	states.texture = &m_tileset;
	//draw the vertex array
	target.draw(m_vertices, states);
}