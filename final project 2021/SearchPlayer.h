#include "Playerdata.h"
#include "Button.h"
#include "TextBox.h"
class SearchPlayer{
	Array<Button> headings;
	Array<Playerdata> players;
	Array<Text> teamname;
	Team* team;
	TextBox box;
public:
	SearchPlayer(Team*team):team(team) {
		string data[9] = { "Name","Shirt no","Average","Runs","Matchwon","Wickets","Type","Ranking","Team" };
		box = TextBox(24, "Search", { 500, 90 }, { 500,40 });
		for (int i = 0; i < 9; i++) {
			headings.append(Button(304 + 89 * i, 200, 300, 25, data[i]));
			headings[i].setzh(0, 5);
		}
		headings[1].setpos(433, 200);
		headings[7].setpos(1000, 200);
		headings[8].setpos(1100, 200);
	}
	void updateclick(RenderWindow& window, Event& event) {
		box.updateclick(window, event);
	}
	void update(Event& event) {
		if (box.update(event))
			setdata(box.getString());
	}
	void setdata(string name) {
		string temp;
		
		while (players.size != 0) {
			players.pop();
			teamname.pop();
		}
		for (int i = 0; i < team->size; i++) {
			for (int j = 0; j < team[i].noofplayers; j++) {
				temp = team[i].player[j].getName();

				//for (int i = 0; i < players.size; i++) {
				//	if (players[i].getname() == temp)ispresent = true;
				//}

				for (int i = 0; temp[i] != '\0'; i++) {
					temp[i] = toupper(temp[i]);
				}
				if (temp.find(name) != -1) {
					teamname.append(Text(team[i].getName(), realfont, 17));
					teamname[teamname.size - 1].setPosition({ 1100,230 + float(teamname.size - 1) * 60 });
					teamname[teamname.size - 1].setFillColor(Color::Black);
					//players.append(Playerdata({ 304,230 + float(players.size) * 60 }, { 900,40 }));
					setplayerdata(i, j);
					cout << temp << " , " << name << endl;
				}
				temp = "";
				
			}
		}
	}

	void setplayerdata(int teamindex,int playerindex) {
		players.append(Playerdata({ 304,230 + float(players.size) * 60 }, { 900,40 }));
		int i = players.size - 1;
		players[i].setstring(team[teamindex].getplayer(playerindex));
	}

	void display(RenderWindow& window) {
		box.display(window);
		for (int i = 0; i < players.size; i++) {
			players[i].display(window);
		}
		for (int i = 0; i < teamname.size; i++) {
			window.draw(teamname[i]);
		}
		for (int i = 0; i < 9; i++) {
			headings[i].display(window);
		}
	}

};

