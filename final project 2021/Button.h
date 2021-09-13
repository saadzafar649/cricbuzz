#include "Includes.h"
#include"GetText.h"
#pragma once
#ifndef BUTTON_H
#define BUTTON_H

class Button{
	string var2;
	bool focus;
	RectangleShape shape;
	Text text;
	Color buttoncolor, textcolor;
public:
	Button(float x = 0, float y = 0, float width = 200, float height = 50, string var = "") {
		buttoncolor = Color(45, 56, 73);
		//217, 219, 241	
		//125, 132, 178 hover
		textcolor = Color::White;
		focus = false;
		realfont.loadFromFile("arial.ttf");
		text.setFont(realfont);
		text.setString(var);
		shape.setPosition(Vector2f(x, y));
		shape.setSize(Vector2f(width, height));
		shape.setFillColor(buttoncolor);
		text.setFillColor(textcolor);
		text.setPosition(shape.getPosition().x + 15, shape.getPosition().y + 5);
		text.setCharacterSize(height - 12);
	};
	void setzh(int z, int h) {
		text.setPosition(shape.getPosition().x + z, shape.getPosition().y + h);
	}
	void setpos(int x, int y) {
		shape.setPosition(Vector2f(x, y));
		text.setPosition(shape.getPosition().x, shape.getPosition().y+5);
	}
	void setstring(string str) {
		text.setString(str);
	}
	void setsize(int x, int y) {
		shape.setSize(Vector2f(x, y));
	}
	bool updateclick(RenderWindow& window, Event& event) {
		return onclick(window);
	}
	bool onclick(RenderWindow& window) {
		Vector2f mouseposition = { float(Mouse::getPosition(window).x),float(Mouse::getPosition(window).y) };

		if (shape.getGlobalBounds().contains(mouseposition)) {
			focus = true;
			shape.setFillColor(Color(71, 110, 177));
			text.setFillColor(Color::White);
			return true;
		}
		else {
			focus = false;
			shape.setFillColor(buttoncolor);
			text.setFillColor(Color::White);
		}
		return false;
	}
	void display(RenderWindow& window) {
		window.draw(shape);
		window.draw(text);
	}


};




#endif // !BUTTON_H