#pragma once
class Input
{
public:
	//key codes start from 0 (A = 0, B = 1, C = 2...) or you can use sf::Keyboard::Keyname
	static bool GetKeyDown(int KeyCode);

	//key codes start from 0 (A = 0, B = 1, C = 2...) or you can use sf::Keyboard::Keyname
	static bool GetKeyUp(int KeyCode);

	//key codes start from 0 (A = 0, B = 1, C = 2...) or you can use sf::Keyboard::Keyname
	static bool GetKey(int KeyCode);

};