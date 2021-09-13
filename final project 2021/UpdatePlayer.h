#include "Team.h"
#include "TextBox.h"

#ifndef UPDATEPLAYER_H
#define UPDATEPLAYER_H

class UpdatePlayer{
	Array<TextBox> box;
	Player* player;
	bool addplayer;
public:
	UpdatePlayer(Player* player, bool addplayer = false) :player(player), addplayer(addplayer) {
		string data[8] = { "Name","Shirt no","Average","Ranking","Total Runs","Matchwon","Wickets","Type" };
		for (int i = 0; i < 8; i++) {
			box.append(TextBox(24, data[i], { 500, 90 + float(i) * 50 }, { 500,40 }));
		}
	}
	bool update(RenderWindow& window, Event& event, Team team[], int& loggedinteam) {
		if (event.key.code != Keyboard::Return) {
			for (int i = 0; i < box.size; i++) {
				box[i].update(event);
			}
		}
		else {
			Player temp(box[0].getString(), box[1].getString(),
				box[2].getString(), box[3].getString(), box[4].getString(),
				box[5].getString(), box[6].getString(), box[7].getString());
			if (!addplayer) {
				player->update(temp, team[loggedinteam].getName());
				for (int i = 0; i < box.size; i++) { box[i].setString(""); box[i].emptystr(); }
			}
			else {
				Player::addplayer(temp, team[loggedinteam].getName());
				team[loggedinteam].noofplayers++;
				team[loggedinteam].player.append(temp);

			}
			return true;
		}
		return false;
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
#endif

