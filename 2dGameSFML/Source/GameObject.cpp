#include "GameObject.h"
#include "Globals.h"

GameObject::GameObject(float m_width, float m_height, std::string m_file_path) {

	// adding the current GameObject ot the GameObjects list
	GameObjects.push_back(this);

	// default values
	color = sf::Color(255, 255, 255, 255); // white


	// checking if the gameObject uses texture
	if (m_file_path.empty()) {
		isTextured = false;
	}
	else {
		isTextured = true;
	}


	// creating the rectangle
	scale = sf::Vector2f(m_width, m_height);

	m_rectangleShape.setSize(scale);

	if (isTextured) {
		
		// loading texture to the rectange object
		if (!m_texture.loadFromFile(m_file_path)) {
			std::cout << "Something went wrong while loading texture" << std::endl;
		}

		m_rectangleShape.setTexture(&m_texture);

	}
}


void GameObject::Draw(sf::RenderWindow& window) {

	m_rectangleShape.setFillColor(color);
	m_rectangleShape.setPosition(sf::Vector2f(position.x,position.y));
	m_rectangleShape.setSize(scale);

	window.draw(m_rectangleShape);
}

void GameObject::SetPosition(float x, float y) {
	position = sf::Vector2f(x,y);
}

void GameObject::SetColor(int R, int G, int B, int A) {
	color = sf::Color(R, G, B, A);
}

void GameObject::SetSize(float Height, float Width) {
	scale = sf::Vector2f(Height, Width);
}

sf::RectangleShape GameObject::GetRectShape() {
	return m_rectangleShape;
}