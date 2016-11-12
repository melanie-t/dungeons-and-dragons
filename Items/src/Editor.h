#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <iterator>
#include "TileMap.h"
#include "Map.h"

using namespace std;

class Editor{
public:
	Editor();

	Editor(int w, int h);

	~Editor();

	void initEditor();

	void initEditor(Map* map);

	void initSprite();

	void initEditorBox();

	void setTile(TileMap map);

	void initText();

	void checkEditorEvent(sf::Event event, TileMap map);

	vector<int> userExit();

	void close();

	vector<int> editorLoop();

private:
	int arrPos;			//current character position
	int tileType;		//type of tile to set down
	int currentMap;
	bool redrawMap;		//if tile added, map is redrawn
	int width, height;

	//SFLW objects
	TileMap map;
	sf::RenderWindow window;
	sf::Texture spriteTexture;
	sf::Texture tileset;
	sf::Sprite sprite;
	sf::Sprite bkgdSprite;
	sf::Text text;
	sf::Text editorText;
	sf::Font font;
	sf::RectangleShape textBox;
	sf::RectangleShape editorBox;
	sf::RectangleShape editorInfo;
};
