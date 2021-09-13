#include "Playerdata.h"
#include "Button.h"
#pragma once
#ifndef PLAYERMENU_H
#define PLAYERMENU_H

class PlayerMenu {
	//Playerdata* players;
	Array<Playerdata> players;
	int noofplayers;
	Array<Button> headings;
	Team* team;
public:
	PlayerMenu(Team* team, int& loggedinteam) {
		string data[8] = { "Name","Shirt no","Average","Runs","Matchwon","Wickets","Type","Ranking" };

		for (int i = 0; i < 8; i++) {
			headings.append(Button(304 + 89 * i, 200, 300, 25, data[i]));
			headings[i].setzh(0, 5);
		}
		headings[1].setpos(433, 200);
		headings[7].setpos(1000, 200);

		this->team = team;
		//players = new Playerdata[team->noofplayers];
		//players = NULL;
		for (int i = 0; i < team[loggedinteam].noofplayers; i++) {
			players.append( Playerdata({ 304,230 + float(i) * 60 }, { 900,40 }, true));
		}

		setplayerdata(loggedinteam);

	}
	
	void setplayerdata(int index) {
		static int noofplayers = team[index].noofplayers;
		if (noofplayers < team[index].noofplayers) {
			noofplayers = team[index].noofplayers;
			players.append(Playerdata({ 304,230 + float(noofplayers) * 60 }, { 900,40 }, true));
		}
		for (int i = 0; i < team[index].noofplayers; i++) {
			players[i] = Playerdata({ 304,230 + float(i) * 60 }, { 900,40 }, true);
			players[i].setstring(team[index].getplayer(i));
		}
	}
	
	int updateclick(RenderWindow& window, Event& event, int& loggedinteam) {
		
		cout << "Asdas";
		
		for (int i = 0; i < team[loggedinteam].noofplayers; i++) {
			if (players[i].deleteclick(window, event, team, loggedinteam, i)) {
				setplayerdata(loggedinteam);
			}
			else if (players[i].updateclick(window, event))return i;
		
		}
		
		return -1;
	}
	
	void display(RenderWindow& window,int&loggedinteam) {
		
		for (int i = 0; i < team[loggedinteam].noofplayers; i++) {
			players[i].display(window);
		}
		
		for (int i = 0; i < 8; i++) {
			headings[i].display(window);
		}
	}
	~PlayerMenu() {

	}
};

#endif