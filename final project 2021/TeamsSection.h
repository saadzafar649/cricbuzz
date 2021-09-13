#include "Teamdata.h"
#include "Playerdata.h"
#pragma once
#ifndef TEAMSSECTION_H
#define TEAMSSECTION_H

class TeamsSection{
	enum TeamsorPlayer {
		teamsshow,
		playershow,
	}state2;
	Teamdata* teams;
	Playerdata* players;
	Array<Button> headings;
	int noofplayers;
	int howmuchtoshow = 6;
public:
	TeamsSection(Team*team) {
		for (int i = 0; i < 8; i++) {
			headings.append(Button(304 , 200 + 89 * i, 300, 25));
			headings[i].setzh(0, 5);
		}
		setforteam();//for initial stage

		state2 = TeamsorPlayer::teamsshow;
		teams = new Teamdata[Team::size];
		for (int i = 0; i < Team::size; i++) {
			teams[i] = Teamdata({ 454 + float(i) * 150 ,74 });
			teams[i].setstring(team + i);
		}
	}

	void updateclick(RenderWindow& window, Event event, Team* team) {
		for (int i = 0; i < Team::size; i++) {
			teams[i].setstring(team + i);
		}
		if(state2 == TeamsorPlayer::teamsshow)
			for (int i = 0; i < Team::size; i++) {
				if (teams[i].update(window, event)) {
					state2 = TeamsorPlayer::playershow;
					setforplayer();
					noofplayers = team[i].noofplayers;
					players = new Playerdata[noofplayers];
					setplayerdata(team, i);
					return;
				}
			}
		else {
			state2 = TeamsorPlayer::teamsshow;
			setforteam();
			delete[]players;
			players = NULL;
		}
	}

	void setforteam() {
		string data[] = { "Team Name","Coach","Captain","Match won","Match lost","Ranking" };
		for (int i = 0; i < 6; i++) {
			headings[i].setpos(305, 74 + 60 * i);
			headings[i].setsize(80, 80);
			headings[i].setstring(data[i]);
		}
		headings[5].setsize(80, 25);
		howmuchtoshow = 6;
	}

	void setforplayer() {
		string data[8] = { "Name","Shirt no","Average","Runs","Matchwon","Wickets","Type","Ranking" };
		for (int i = 0; i < 8; i++) {
			headings[i].setstring(data[i]);
			headings[i].setzh(0, 5);
			headings[i].setpos(304 + 89 * i, 80);
			headings[i].setsize(300, 35);
		}
		headings[1].setpos(433, 80);
		headings[7].setpos(1000, 80);
		howmuchtoshow = 8;
	}

	void setplayerdata(Team* team, int index) {
		for (int i = 0; i < noofplayers; i++) {
			players[i] = Playerdata({ 304,130 + float(i) * 60 });
			players[i].setstring(team[index].getplayer(i));
		}
	}

	void display(RenderWindow& window) {
		for (int i = 0; i < howmuchtoshow; i++) {
			headings[i].display(window);
		}
		switch (state2) {
		case TeamsorPlayer::teamsshow:
			for (int i = 0; i < Team::size; i++) {
				teams[i].display(window);
			}
			break;
		case TeamsorPlayer::playershow:
			for (int i = 0; i < noofplayers; i++) {
				players[i].display(window);
			}
		}
	}
	
	~TeamsSection() {
		delete[]teams;
		delete[]players;
	}
};


#endif // !TEAMSSECTION_H