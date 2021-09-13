#include "Team.h"
#include "TextBox.h"

#ifndef UPDATETEAM_h
#define UPDATETEAM_h

class UpdateTeam{
	Array<TextBox> box;
	Team* team;
public:
	UpdateTeam(Team* team) :team(team) {
		string data[8] = { "name", "match Won", "match Lost", "captain", "coach", "ranking", "username", "password" };
		for (int i = 0; i < 8; i++) {
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
	void updateclick(RenderWindow& window, Event& event) {
		for (int i = 0; i < box.size; i++) {
			box[i].updateclick(window, event);
		}
	}
	void savetofile(int& loggedinteam) {
		string filename = "files/" + team[loggedinteam].name + ".txt";
		string temp, filedata = "";
		fstream file;

		{
			filename = "files/Teams.txt";
			file.open(filename);
			//reading file data
			while (!file.eof()) {
				getline(file, temp);
				filedata += temp;
				if (!file.eof())filedata += "\n";
			}
			file.close();
			//raplacing name
			temp = box[0].getString();
			converttolower(temp);
			if (temp != "") {
				string temp3 = team[loggedinteam].name;
				filedata.replace(filedata.find(temp3), temp3.length(), temp);
			}
			//username
			temp = box[6].getString();
			if (temp != "") {
				string temp3 = team[loggedinteam].username;
				filedata.replace(filedata.find(temp3), temp3.length(), temp);
			}
			//password
			temp = box[7].getString();
			if (temp != "") {
				string temp3 = team[loggedinteam].password;
				filedata.replace(filedata.find(temp3), temp3.length(), temp);
			}
			file.open(filename);
			file << filedata;
			filedata = "";
			file.close();
		}


		{
			filename = "files/" + team[loggedinteam].name + ".txt";
			team[loggedinteam].updateteam(Team(box[0].getString(),
				box[1].getString(), box[2].getString(), box[3].getString(),
				box[4].getString(), box[5].getString(), box[6].getString(),
				box[7].getString()));


			//reading data
			file.open(filename);
			getline(file, temp);
			getline(file, temp);
			filedata += temp;
			file.close();

			//changing name of file
			if (box[0].getString() != "") {
				remove(&filename[0]);
				filename = "files/" + team[loggedinteam].name + ".txt";
			}
			//putting data in particular team file
			file.open(filename, ios::out);
			file << team[loggedinteam].matchWon << ",";
			file << team[loggedinteam].matchLost << ",";
			temp = team[loggedinteam].coach;
			converttolower(temp);
			file << temp << ",";
			temp = team[loggedinteam].captain;
			converttolower(temp);
			file << temp << ",";
			file << team[loggedinteam].ranking << endl;
			file << filedata;
			file.ignore();
			file.close();
		}

	}
	void converttolower(string& temp) {
		for (int i = 1; i<temp.length(); i++) {
			temp[i] = tolower(temp[i]);
		}
	}
	void display(RenderWindow& window) {
		for (int i = 0; i < box.size; i++) {
			box[i].display(window);
		}
	}

};



#endif