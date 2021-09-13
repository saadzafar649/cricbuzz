#include "Includes.h"
#include "TextBox.h"
#include "Team.h"
#include "PlayerMenu.h"
#include "UpdatePlayer.h"
#include "ScheduleMatch.h"
#include "UpdateTeam.h"
#ifndef LOGIN_H
#define LOGIN_H

Texture texture;
class Login:public Sprite{
	TextBox username;
	TextBox password;
	string name, pass;
	Text incorrect;
	Array<Button> options;
	enum class Loginprogress {
		login,
		showplayer,
		addplayer,
		updateplayer,
		match,
		updateteam,
	}progress = Loginprogress::login;
	PlayerMenu* playermenu;
	UpdatePlayer* updatePlayer;
	UpdatePlayer* addPlayer;
	ScheduleMatch* scheduelematch;
	UpdateTeam* updateTeam;
	
public:
	Login() {
		username = TextBox(24,"Username : ", { 500, 200 }, {500,40});
		password = TextBox(24,"Password : ", { 500, 350 }, {500,40});
		setTexture(texture);
		incorrect.setFont(realfont);
		incorrect.setFillColor(Color::Red);
		incorrect.setPosition({ 500,500 });

		username.setString("");
		password.setString("");

		playermenu = NULL;
		updatePlayer = NULL;
		addPlayer = NULL;
		scheduelematch = NULL;
		updateTeam = NULL;
		
		string optionsdata[] = { "Add Player","Scheduele match", "Update Team","logout" };

		options.append(Button(405, 120, 120, 30, optionsdata[0]));
		options.append(Button(520, 120, 170, 30, optionsdata[1]));
		options.append(Button(690, 120, 170, 30, optionsdata[2]));
		options.append(Button(820, 120, 120, 30, optionsdata[3]));
	}
	void update(RenderWindow&window,Event& event, Team team[], int& loggedinteam) {
		int clickindex;
		switch (progress) {
		case Loginprogress::login:
			if (event.key.code != Keyboard::Return) {
				username.update(event);
				password.update(event);
			}
			else if (event.key.code == Keyboard::Return) {
				name = username.getString();
				pass = password.getString();
				loggedinteam = validateteam(team, name, pass);
				//incase login is correct
				if (loggedinteam != -1) {
					progress = Loginprogress::showplayer;
					incorrect.setString("");
					username.setString("");
					password.setString("");
					username.emptystr();
					password.emptystr();
					if (!playermenu) {
						playermenu = new PlayerMenu(team, loggedinteam);
					}
					cout << "e";
				}
				//incase it is not correct
				else incorrect.setString("Incorrect username and password");
				//showing player update functions
			}
			break;
		case Loginprogress::updateplayer:
			if (updatePlayer->update(window, event, team, loggedinteam)) {
				progress = Loginprogress::showplayer;
				playermenu->setplayerdata( loggedinteam);
			}
			break;
		case Loginprogress::addplayer:
			if (addPlayer->update(window, event, team, loggedinteam)) {
				progress = Loginprogress::showplayer;
				playermenu->setplayerdata(loggedinteam);
			}
			break;
		case Loginprogress::match:
			if (scheduelematch->update(window, event, loggedinteam))progress = Loginprogress::showplayer;
			break;



		case Loginprogress::updateteam:
			if (updateTeam->update(window, event, loggedinteam))progress = Loginprogress::showplayer;
		}
	}
	int validateteam(Team* team,string username,string password) {
		for(int i = 0; i < Team::size; i++) {
			if (team[i].is_valid(username, password))return i;
		}
		return -1;
	}
	void updateclick(RenderWindow& window, Event& event, Team team[], int& loggedinteam) {
		int clickindex;
		switch (progress) {
		case Loginprogress::login:
			username.updateclick(window, event);
			password.updateclick(window, event);
			break;
		case Loginprogress::showplayer:
			cout << "e";
			clickindex = playermenu->updateclick(window, event, loggedinteam);
			if (clickindex != -1) {
				progress = Loginprogress::updateplayer;
				if (!updatePlayer) {
					updatePlayer = new UpdatePlayer(&team[loggedinteam].player[clickindex]);
				}
			}
			if (options[0].updateclick(window, event)) {
				if (!addPlayer) {
					addPlayer = new UpdatePlayer(&team[loggedinteam].player[clickindex], true);
				}
				progress = Loginprogress::addplayer;
			}
			else if (options[1].updateclick(window, event)) {
				if (!scheduelematch) {
					scheduelematch = new ScheduleMatch(team);
				}
				progress = Loginprogress::match;
			}
			else if (options[2].updateclick(window, event)) {
				if (!updateTeam)
					updateTeam = new UpdateTeam(team);
				progress = Loginprogress::updateteam;
			}
			else if (options[3].updateclick(window, event)) {
				loggedinteam = -1;
				progress = Loginprogress::login;
			}
			break;


		case Loginprogress::updateplayer:
			updatePlayer->updateclick(window, event);
			break;


		case Loginprogress::addplayer:
			addPlayer->updateclick(window, event);
			break;


		case Loginprogress::match:
			scheduelematch->updateclick(window, event);
			break;


		case Loginprogress::updateteam:
			updateTeam->updateclick(window, event);
			break;
		}
	}
	void display(RenderWindow& window, int& loggedinteam) {
		switch (progress) {
		case Loginprogress::login:
			window.draw(*this);
			username.display(window);
			password.display(window);
			window.draw(incorrect);
			break;
		case Loginprogress::showplayer:
			playermenu->display(window, loggedinteam);
			options[0].display(window);
			options[1].display(window);
			options[2].display(window);
			options[3].display(window);
			break;
		case Loginprogress::updateplayer:
			updatePlayer->display(window);
			break;
		case Loginprogress::addplayer:
			addPlayer->display(window);
			break;
		case Loginprogress::match:
			scheduelematch->display(window);
			break;
		case Loginprogress::updateteam:
			updateTeam->display(window);
			break;
		}
	}
};

#endif // !LOGIN_H