#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class GameObject
{
private:

	bool isTextured;
	sf::RectangleShape m_rectangleShape;
	sf::Texture m_texture;
	sf::Vector2f scale;
	sf::Vector2f position;
	sf::Color color;

public:
	bool AutomaticDrawing = true;
	float speed;
	
	// movement
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;

	GameObject(float m_width, float m_height, std::string m_file_path = "");

	void SetPosition(float x, float y);
	void SetColor(int R, int G, int B, int A = 255);
	void SetSize(float Height, float Width);
	sf::RectangleShape GetRectShape();


	void Draw(sf::RenderWindow& window);
};

