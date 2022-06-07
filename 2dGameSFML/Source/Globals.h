#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObject.h"
#include "Text.h"
#include <list>

extern sf::RenderWindow* Main_Engine_Window;

extern sf::Event* Main_Engine_Event;

extern std::list<GameObject*> GameObjects;

extern std::list<Text*> TextObjects;

extern float DeltaTime;