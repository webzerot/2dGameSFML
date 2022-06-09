#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>


#include "Engine.h"
#include "../Game.h"

const int Engine_Window_Width = 700;
const int Engine_Window_Height = 500;
const std::string Engine_Window_Title = "Engine Window";

int main(int argc, char* argv[]) {

	// hiding console at start
	Console::Show();

	// creating the window
	Main_Engine_Window = new sf::RenderWindow(
		sf::VideoMode(Engine_Window_Width, Engine_Window_Height),
		Engine_Window_Title,
		sf::Style::Default);

	Main_Engine_Window->setFramerateLimit(60);

	Start();

	// creating the window events
	Main_Engine_Event = new sf::Event;
	
	sf::Clock deltaClock; // used for measuring DeltaTime

	// main loop
	while (Main_Engine_Window->isOpen()) {

		sf::Time Time_From_Last_Frame = deltaClock.restart();
		DeltaTime = Time_From_Last_Frame.asSeconds();

		// event loop
		while (Main_Engine_Window->pollEvent(*Main_Engine_Event)) {

			if (Main_Engine_Event->type == sf::Event::Closed) {
				Main_Engine_Window->close();
			}

			EventUpdate();

			// keyboard keydown events
			if (Main_Engine_Event->type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					// do something when space is pressed
				}
			}
		}

		//clearing window
		Main_Engine_Window->clear();

		Update();

		// drawing

		// GameObjects
		for (GameObject* Current_GameObject : GameObjects) {
			if (Current_GameObject->AutomaticDrawing)
				Current_GameObject->Draw(*Main_Engine_Window);
		}
		// TextObjects
		for (Text* Current_Text_Object : TextObjects) {
			if (Current_Text_Object->AutomaticDrawing)
				Current_Text_Object->Draw(*Main_Engine_Window);
		}

		Main_Engine_Window->display();
	}

	delete Main_Engine_Window;
	delete Main_Engine_Event;

	return EXIT_SUCCESS;
}