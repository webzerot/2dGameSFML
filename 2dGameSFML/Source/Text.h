#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Text {

private:
	sf::Font font;
	sf::Text text;

	std::string String_text;
	std::string default_font = "Anton.ttf";

	sf::Vector2f position;
	sf::Color color;

public:

	int fontSize = 10;
	bool AutomaticDrawing = true;

	Text(std::string& m_text, std::string filePath = "");
	void setPosition(float x, float y);
	void SetColor(int R, int G, int B, int A);

	void Draw(sf::RenderWindow& window);
};

