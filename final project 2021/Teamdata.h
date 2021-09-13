#include "Includes.h"
#include "Team.h"
#pragma once
#ifndef TEAMDATA_H
#define TEAMDATA_H
static Font fonttemp;
class Teamdata{
	RectangleShape shape;
	Text data[6];
public:
	Teamdata(Vector2f position = { 300,300 }, Vector2f size = { 147,330 }) {//530
		fonttemp.loadFromFile("arial.ttf");
		shape.setPosition(position);
		shape.setSize(size);
		shape.setFillColor(Color(200, 200, 200));

		for (int i = 0; i < 6; i++) {
			data[i].setFont(realfont);
			data[i].setFillColor(Color(45, 56, 73));
			data[i].setPosition(position.x + 10, position.y + 60 * i);
			data[i].setCharacterSize(18);
		}
	}
	void setstring(Team* team) {
		data[0].setString(team->getName());
		data[1].setString(team->getcoach());
		data[2].setString(team->getcaptain());
		data[3].setString(team->getmatchWon());
		data[4].setString(team->getmatchLost());
		data[5].setString(team->getranking());
	}
	bool update(RenderWindow& window, Event& event) {
		return onclick(window);
	}
	bool onclick(RenderWindow& window) {
		Vector2f mouseposition = { float(Mouse::getPosition(window).x),float(Mouse::getPosition(window).y) };
		if (shape.getGlobalBounds().contains(mouseposition)) {
			return true;
		}
		return false;
	}
	void display(RenderWindow& window) {
		window.draw(shape);
		for (int i = 0; i < 6; i++) {
			window.draw(data[i]);
		}
	}
};

#endif // !TEAMDATA_H
