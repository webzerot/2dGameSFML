#pragma once

#include <iostream>
#include <SFML/Audio.hpp>

class Sound {
private:
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
public:
	Sound(const std::string& Sound_Path) {

		if (!soundBuffer.loadFromFile(Sound_Path)) {
			std::cout << "Sound Was not loaded" << std::endl;
			return;
		}

		sound.setBuffer(soundBuffer);
	}


	void Play() {
		sound.play();
	}
	void Stop() {
		sound.stop();
	}

};

class Music {
private:

public:
	sf::Music music;

	Music(const std::string& Music_Path) {
		if (!music.openFromFile(Music_Path)) {
			std::cout << "Music Not Loaded!" << std::endl;
			return;
		}
	}

	void LoadMusic(std::string Music_Path) {

		if (!music.openFromFile(Music_Path)) {
			std::cout << "Music Not Loaded!" << std::endl;
			return;
		}
	}

	void Play() {
		music.play();
	}
	void Stop() {
		music.stop();
	}
	void Pause() {
		music.pause();
	}
};
