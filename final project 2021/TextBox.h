#include "Includes.h"
#include "GetText.h"
#pragma once
#ifndef TEXTBOX_H
#define TEXTBOX_H

class TextBox:public GetText {
	bool focus;
	RectangleShape shape;
	Text text;
public:
	TextBox(int limit = 10, string txt = "", Vector2f position = { 100,0.0 }, Vector2f size = { 300,20 },
		Color color = Color::White) :GetText(limit) {

		text.setFont(realfont);
		text.setString(txt);
		text.setCharacterSize(size.y - 10);
		text.setPosition(position.x - 180, position.y);
		text.setFillColor(Color::Black);

		focus = false;
		GetText::Text::setPosition({ position.x ,position.y  });
		GetText::Text::setCharacterSize(size.y - 10);
		shape.setOutlineColor(Color(70, 56, 73));
		shape.setOutlineThickness(2);
		shape.setFillColor(color);
		shape.setSize(size);
		shape.setPosition(position);
	}
	bool update(Event& event) {
		if (focus)
			return GetText::update(event);
		return false;
	}
	void updateclick(RenderWindow&window, Event& event) {
		onclick(window);
	}
	void onclick(RenderWindow&window ) {
		Vector2f mousepos = { float(Mouse::getPosition(window).x),float(Mouse::getPosition(window).y) };
		if (shape.getGlobalBounds().contains(mousepos)) {
			focus = true;
			shape.setOutlineColor(Color::Black);
		}
		else { 
		focus = false; 
		shape.setOutlineColor(Color::Green);
		}

	}
	void display(RenderWindow& window) {
		window.draw(shape);
		window.draw(*this);
		window.draw(text);
	}
};
#endif // !TEXTBOX_H