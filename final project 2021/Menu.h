#include "Includes.h"
#include"Button.h"
#include"Array.h"
#pragma once

Texture texture1;
class Menu:public Sprite{
	string var1[6] = { "Teams","Matches","Search Player","World Records","News","Login" };
	Array<Button> button;
public:
	Menu() {
		texture1.loadFromFile("UI.png");
		for (int i = 0; i < 6; i++) {
			button.append(Button(58, (74 + i * 60), 245, 40, var1[i]));
		}
		setTexture(texture1);
	}
	void updateclick(RenderWindow& window, Event event) {
		for (int i = 0; i < button.size; i++) {
			if (button[i].updateclick(window, event))state = static_cast<State1>(i);
		}
	}
	void display(RenderWindow& window) {
		window.draw(*this);
		for (int i = 0; i < button.size; i++) {
			button[i].display(window);
		}
	}
};

