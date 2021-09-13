#include "Team.h"
#include "Button.h"
#pragma once
#ifndef PLAYERDATA_H
#define PLAYERDATA_H

class Playerdata{
	RectangleShape shape;
	Text data[8];
	bool teamview = false;
	Button del;
public:
	Playerdata(Vector2f position = { 300,300 }, Vector2f size = { 900,40 }, bool teamview = false) :teamview(teamview)
		,del(position.x+size.x-130,position.y,120,size.y,"Delete") {

		shape.setPosition(position);
		shape.setSize(size);
		shape.setFillColor(Color(200, 200, 200));
		for (int i = 0; i < 8; i++) {
			data[i].setFont(realfont);
			data[i].setFillColor(Color::Black);
			data[i].setPosition(position.x + 90 * i, position.y);
			data[i].setCharacterSize(17);
		}
		data[1].setPosition(position.x + 130, position.y);
		data[7].setPosition(position.x + 700, position.y);
	}
	string getname() {
		return data[0].getString();
	}
	void setstring(Player* player) {
		data[0].setString(player->getName());
		data[1].setString(player->getShirtNo());
		data[2].setString(player->getAverage());
		data[3].setString(player->getRuns());
		data[4].setString(player->getMatch());
		data[5].setString(player->getwickets());
		data[6].setString(player->gettype());
		data[7].setString(player->getRanking());
	}
	bool deleteclick(RenderWindow& window, Event& event, Team* team, int& loggedinteam,int&index) {
		if (del.updateclick(window, event)) {
			cout << "lol";
			//team[loggedinteam].getplayer(index)->removeplayer(team[loggedinteam].getname());
			team[loggedinteam].removeplayer(index);
			return true;
		}
	}
	bool updateclick(RenderWindow& window, Event& event) {
		return onclick(window);
		cout << "lol22";
	}
	bool onclick(RenderWindow& window) {
		Vector2f mouseposition = { float(Mouse::getPosition(window).x),float(Mouse::getPosition(window).y) };
		if (shape.getGlobalBounds().contains(mouseposition)) {
			shape.setFillColor(Color::White);
			return true;
		}
		else {
			shape.setFillColor(Color(200, 200, 200));
		}
		return false;
	}
	void display(RenderWindow& window) {
		window.draw(shape);
		if (teamview)del.display(window);
		for (int i = 0; i < 8; i++) {
			window.draw(data[i]);
		}
	}
};


#endif // !PLAYERDATA_H