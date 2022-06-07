#include "Globals.h"
#include <SFML/Graphics.hpp>
#include <list>
#include "Text.h"
#include "GameObject.h"

// the Game Window
sf::RenderWindow* Main_Engine_Window;

// main widow events
sf::Event* Main_Engine_Event;

// GameObjects
std::list<GameObject*> GameObjects;

// Text Objects
std::list<Text*> TextObjects;

// DeltaTime
float DeltaTime;
