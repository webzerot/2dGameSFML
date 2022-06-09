#include "Text.h"
#include "Globals.h"

Text::Text(std::string m_text, std::string filePath) {

	TextObjects.push_back(this);

	if (!filePath.empty()) {

		if (!font.loadFromFile(filePath)) {
			std::cout << "Something went wrong when openning the font file" << std::endl;
		}
	}
	else {
		if (!font.loadFromFile(default_font)) {
			std::cout << default_font << " was not found" << std::endl;
		}
	}

	text.setFont(font);

}

void Text::Draw(sf::RenderWindow& window) {

	text.setPosition(position);
	text.setCharacterSize(fontSize);
	text.setString(String_text);
	text.setFillColor(color);

	window.draw(text);
}

void Text::setPosition(float x, float y) {
	position = sf::Vector2f(x, y);
}

void Text::SetColor(int R, int G, int B, int A) {
	color = sf::Color(R, G, B, A);
}

void Text::ChangeText(std::string newText) {
	text.setString(newText);
}