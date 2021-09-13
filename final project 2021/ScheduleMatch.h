#include "TextBox.h"
#include "Array.h"
#include "Team.h"
#ifndef SCHEDUELEMATCH_H
#define SCHEDUELEMATCH_H


class ScheduleMatch {
	Array<TextBox> box;
	Team* team;
public:
	ScheduleMatch(Team*team):team(team) {
		string data[] = { "team2", "date", "venue", "matchtype", "comentators", "umpires", "matchstatus" };
		for (int i = 0; i < 7; i++) {
			box.append(TextBox(24, data[i], { 500, 90 + float(i) * 50 }, { 500,40 }));
		}
	}

	bool update(RenderWindow& window, Event& event, int& loggedinteam) {
		if (event.key.code != Keyboard::Return) {
			for (int i = 0; i < box.size; i++) {
				box[i].update(event);
			}
		}
		else {
			savetofile(loggedinteam);
			return true;
		}
		return false;
	}
	void savetofile(int& loggedinteam) {
		fstream file("files/matches.txt", ios::app);
		string temp;
		file << team[loggedinteam].getName() << ",";
		for (int i = 0; i < box.size; i++) {
			temp = box[i].getString();
			box[i].emptystr();//emptying string
			box[i].setString("");//emptying the text string which is rendered
			if (temp != "") {
				for (int i = 1; temp[i] != '\0'; i++) {
					temp[i] = tolower(temp[i]);
				}
				file << temp << ",";
			}
		}
		file << endl; file.close();
	}
	void updateclick(RenderWindow& window, Event& event) {
		for (int i = 0; i < box.size; i++) {
			box[i].updateclick(window, event);
		}
	}
	
	void display(RenderWindow& window) {
		for (int i = 0; i < box.size; i++) {
			box[i].display(window);
		}
	}


};

#endif // !SCHEDUELEMATCH_H
