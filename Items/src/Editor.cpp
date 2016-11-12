#include "Editor.h"

int arrPos;		//current character position
int tileType;	//type of tile to set down
bool redrawMap;	//if tile added, map is redrawn
int width, height;
vector<int> newLevel;
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
sf::RectangleShape highLight;


Editor::Editor(){
	//default dimensions of the editor
	width = 20;
	height = 10;
	newLevel.resize(width*height);
};

Editor::Editor(int w, int h){
	width = w;
	height = h;
	newLevel.resize(width*height);
};

Editor::~Editor(){}

// initializes the editor params
void Editor::initEditor(){
	cout << "Loading background tilemap..." << endl;
	arrPos = 0;
	tileType = 0;
	redrawMap = false;
	// create and prefill new level with empty tiles
	for (int k = 0; k < newLevel.size(); k++){
		newLevel[k] = 8;
	}

	//load the blank map
	map.load("bkrd.png", sf::Vector2u(32, 32), newLevel, width, height);
	map.setPosition(25, 25);

	//draw the window space
	window.create(sf::VideoMode(800, 600), "DND Editor!");
	window.setKeyRepeatEnabled(false);
	initSprite();
}

void Editor::initEditor(Map* mapLoad){
	cout << "Loading background tilemap..." << endl;
	arrPos = 0;
	tileType = 0;
	redrawMap = false;
	// create and prefill new level with empty tiles
	for (int k = 0; k < newLevel.size(); k++){
		newLevel[k] = 8;
	}
	width = mapLoad->getNumRows();
	height = mapLoad->getNumCol();
	newLevel.resize(width*height);
	newLevel = mapLoad->outputMap();

	//load the blank map
	map.load("bkrd.png", sf::Vector2u(32, 32), newLevel, width, height);
	map.setPosition(25, 25);

	//draw the window space
	window.create(sf::VideoMode(800, 600), "DND Editor!");
	window.setKeyRepeatEnabled(false);
	initSprite();
}

// creates the sprite to handle the tiles
void Editor::initSprite() {
	//sprite in editor takes from tileset
	if (!spriteTexture.loadFromFile("bkrd.png"))
	{
		cout << "error loading tile sprite" << endl;
	}
	sprite.setTexture(spriteTexture);
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	sprite.setColor(sf::Color(255, 255, 255, 170));
	sprite.setPosition(25, 25);

	highLight.setSize(sf::Vector2f(32, 32));
	highLight.setOutlineColor(sf::Color(255, 120, 20, 150));
	highLight.setFillColor(sf::Color(200, 90, 10, 20));
	highLight.setPosition(25, 25);
	highLight.setOutlineThickness(2);

	initEditorBox();
}

//intiializes editor box 
void Editor::initEditorBox() {
	editorBox.setSize(sf::Vector2f(width * 32, height * 32));
	editorBox.setPosition(sf::Vector2f(25, 25));
	editorBox.setFillColor(sf::Color::Yellow);
	editorBox.setOutlineColor(sf::Color::Blue);
	editorBox.setOutlineThickness(5);

	editorInfo.setSize(sf::Vector2f(20 * 32 - 24, 100));
	editorInfo.setPosition(37, height * 32 + 45);
	editorInfo.setFillColor(sf::Color(200, 200, 190));
	editorInfo.setOutlineColor(sf::Color(50, 190, 190));
	editorInfo.setOutlineThickness(3);

	initText();
}

//initializes editor information for user
void Editor::initText() {
	if (!font.loadFromFile("font.ttf"))
	{
		cout << "Font load error" << endl;
	}

	// select the font
	text.setFont(font); // font is a sf::Font


	string tileInfo = "[space] to set a tile!\n[0-9] to choose tile type\nFor a door tile [6] check the console to set the parameters\nTODO: SET AND LINK DOORS";
	text.setString(tileInfo);
	text.setCharacterSize(15); // in pixels, not points!
	text.setFillColor(sf::Color(20, 20, 40));
	text.setStyle(sf::Text::Bold);
	text.setPosition(50, height * 32 + 50);

	// textbox settings
	textBox.setSize(sf::Vector2f(width * 32 - 24, 200));
	textBox.setPosition(12, height * 32 + 5);
	textBox.setFillColor(sf::Color(200, 200, 190));
	textBox.setOutlineColor(sf::Color(50, 190, 190));
	textBox.setOutlineThickness(3);

}

//keypress check
void Editor::checkEditorEvent(sf::Event event, TileMap map) {
	// game keypress
	switch (event.type)
	{
		// key pressed, change 
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::Space) {
			newLevel[arrPos] = tileType;
			redrawMap = true;
		}
		if (event.key.code == sf::Keyboard::Up) {
			//prevents movement past top boundary of map area
			if ((arrPos - width) < 0) break;
			sprite.move(0, -32);
			highLight.move(0, -32);
			arrPos -= width;
			break;
		}
		else if (event.key.code == sf::Keyboard::Down) {
			//prevents movement past bottom boundary of map area
			if ((arrPos + width) >= newLevel.size()) break;
			sprite.move(0, 32);
			highLight.move(0, 32);
			arrPos += width;
			break;
		}
		else if (event.key.code == sf::Keyboard::Left) {
			//prevents movement past left boundary of map area
			if ((arrPos - 1) < 0) break;
			else if (arrPos % width == 0) break;
			sprite.move(-32, 0);
			highLight.move(-32,0);
			arrPos--;
			break;
		}
		else if (event.key.code == sf::Keyboard::Right) {
			//prevents movement past right boundary of map area
			if ((arrPos + 1) > newLevel.size()) break;
			else if ((arrPos + 1) % width == 0) break;
			sprite.move(32, 0);
			highLight.move(32,0);
			arrPos++;
			break;
		}
		else if (event.key.code == sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Numpad0) {
			tileType = 0;
			sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
			break;
		}
		else if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
			tileType = 1;
			sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
			break;
		}
		else if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
			tileType = 2;
			sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
			break;
		}
		else if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
			tileType = 3;
			sprite.setTextureRect(sf::IntRect(96, 0, 32, 32));
			break;
		}
		else if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4) {
			tileType = 4;
			sprite.setTextureRect(sf::IntRect(128, 0, 32, 32));
			break;
		}
		else if (event.key.code == sf::Keyboard::Num5 || event.key.code == sf::Keyboard::Numpad5) {
			tileType = 5;
			sprite.setTextureRect(sf::IntRect(160, 0, 32, 32));
			break;
		}
		else if (event.key.code == sf::Keyboard::Num6 || event.key.code == sf::Keyboard::Numpad6) {
			tileType = 6;
			sprite.setTextureRect(sf::IntRect(192, 0, 32, 32));
			break;
		}
		else if (event.key.code == sf::Keyboard::Num7 || event.key.code == sf::Keyboard::Numpad7) {
			tileType = 7;
			sprite.setTextureRect(sf::IntRect(224, 0, 32, 32));
			break;
		}
		else if (event.key.code == sf::Keyboard::Num8 || event.key.code == sf::Keyboard::Numpad8) {
			tileType = 8;
			sprite.setTextureRect(sf::IntRect(256, 0, 32, 32));
			break;
		}
		else if (event.key.code == sf::Keyboard::Num9 || event.key.code == sf::Keyboard::Numpad9) {
			tileType = 9;
			sprite.setTextureRect(sf::IntRect(288, 0, 32, 32));
			break;
		}
	}

}

//sets the tile type at the current position
void Editor::setTile(TileMap map) {
	newLevel[arrPos] = tileType;
}

void Editor::close(){
	window.close();
}

//editor driver loop
vector<int> Editor::editorLoop(){

	cout << "Starting Editor:" << endl;
	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			//escape returns the array, does not close window
			if (sf::Event::Closed || event.key.code == sf::Keyboard::Escape){
				
				cout << "\n\n--------------\n";
				for (int k = 0; k < newLevel.size(); k++){
					if (k % width == 0) cout << endl;
					cout << newLevel[k];
				}
				cout << "\n-----------------\n\n";
				return newLevel;
			}
			if (event.key.code == sf::Keyboard::B){
				return newLevel;
			}
			checkEditorEvent(event, map);
		}

		//if user sets a new tile, map is redrawn
		if (redrawMap) {
			map.setMap(sf::Vector2u(32, 32), newLevel, width, height);
			cout << "width " << width << " height " << height;
			cout << "\n" << tileType << endl;
			cout << "\n" << arrPos << endl;
			for (int k = 0; k < newLevel.size(); k++){
				if (k % width == 0) cout << endl;
				cout << newLevel[k];
			}
			cout << endl;
			redrawMap = false;
		}

		//draws editor
		window.clear();

		window.draw(editorBox);
		window.draw(map);
		window.draw(sprite);
		window.draw(highLight);
		window.draw(editorInfo);
		window.draw(text);

		window.display();
	}
	cout << "\nend editor" << endl;
	return newLevel;
}

