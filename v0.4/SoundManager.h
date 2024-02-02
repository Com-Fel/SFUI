#pragma once
#include"UI.h"
namespace UI {
	class Sound {
	private:
		sf::SoundBuffer buf;

	public:
		sf::Sound sound;

		string name;
		string filePath;
		Sound(string name,string filePath) {
			buf.loadFromFile(filePath);
			sound.setBuffer(buf);
			this->name = name;
		}
	};

	class SoundManager {
	private:
		vector<Sound*> sounds;

	public:

		void loadSound(string name, string filePath) {
			sounds.push_back(new Sound(name, filePath));
		}
		 
		void playSound(string soundName) {
			for (int i = 0;i < sounds.size();i++) {
				if (sounds[i]->name == soundName) {
					sounds[i]->sound.play();

					break;
				}
			}
		}
	};
}