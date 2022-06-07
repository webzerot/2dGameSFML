#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>


#include "Globals.h"
#include "GameObject.h"
#include "Text.h"
#include "Input.h"
#include "Sound.h"

#define Key sf::Keyboard

class Console {
public:
	static void Hide() {
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}
	static void Show() {
		ShowWindow(GetConsoleWindow(), SW_SHOW);
	}
};