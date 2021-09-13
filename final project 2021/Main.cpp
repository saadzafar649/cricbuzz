#include "GetText.h"
#include "Array.h"
#include "Login.h"
#include "Menu.h"
#include "Team.h"
#include "TeamsSection.h"
#include "SearchPlayer.h"
#include "Matches.h"
#include "WorldRecord.h"

int Team::size = 0;


int main() {

	realfont.loadFromFile("arial.ttf");
	string name = "files/Teams.txt", username, password;
	ifstream file;
	file.open(name);


	while (!file.eof()) {
		string str;
		getline(file, str, '\n');
		if (!file.eof())
			Team::size++;
	}
	file.close();
	int loggedinteam = -1;

	//yesorno();
	Team* teams = new Team[Team::size];
	int i = 0;

	file.open(name);
	while (!file.eof()) {
		getline(file, name, ',');
		getline(file, username, ',');
		file >> password;
		cout << name << endl;
		file.ignore();
		if (!file.eof()) {
			ifstream file2("files/" + name + ".txt");
			if (file2.good()) {
				teams[i].getfiles(name, username, password, file2);
				i++;
				file2.close();
			}
		}
	}
	file.close();



	RenderWindow window(VideoMode(1200, 580), "Cricbuzz");
	state = State1::teams;
	Login login;
	Menu menu;
	WorldRecords worldrecord;
	//WorldRecords news(true);//for news
	SearchPlayer searchPlayer(teams);
	TeamsSection teamsection(teams);
	Matches obj;
	Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				switch (state) {
				case State1::loginState:
					login.update(window, event, teams, loggedinteam);
					break;
				case State1::searchplayer:
					searchPlayer.update(event);
					break;
				}
				break;
			case Event::MouseButtonReleased:
				menu.updateclick(window, event);
				switch (state) {
				case State1::loginState:
					login.updateclick(window, event, teams, loggedinteam);
					break;
				case State1::searchplayer:
					searchPlayer.updateclick(window, event);
					break;
				case State1::teams:
					teamsection.updateclick(window, event, teams);
					break;
				}
				break;
			}
		}

		//switch (state) {
		//	case State1::mainscreen:
		//		menu.alwaysupdate(window);
		//}

		switch (state) {
		case State1::loginState:

			break;
		}

		window.clear(Color::White);
		menu.display(window);
		switch (state) {
		case State1::matches:
			obj.display(window);
			break;
		case State1::loginState:
			login.display(window, loggedinteam);
			break;
		case State1::teams:
			teamsection.display(window);
			break;
		case State1::searchplayer:
			searchPlayer.display(window);
			break;
		case State1::news:
		case State1::worldrecords:
			worldrecord.display(window);
			break;
		}
		window.display();
	}
	return 0;
}