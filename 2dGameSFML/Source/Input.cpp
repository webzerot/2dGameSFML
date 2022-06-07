#include "Input.h"
#include "Globals.h"
#include <SFML/Graphics.hpp>

bool Input::GetKeyDown(int KeyCode) {

	sf::Event evt = *Main_Engine_Event;

	if (evt.type == sf::Event::KeyPressed) {
		if (evt.key.code == KeyCode) {
			return true;
		}
	}
	return false;
}
bool Input::GetKeyUp(int KeyCode) {

	sf::Event evt = *Main_Engine_Event;

	if (evt.type == sf::Event::KeyReleased) {
		if (evt.key.code == KeyCode) {
			return true;
		}
	}
	return false;
}
bool Input::GetKey(int KeyCode) {

	sf::Event evt = *Main_Engine_Event;

	if (evt.key.code == KeyCode) {
		return true;
	}
	return false;
}