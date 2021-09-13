#include "Array.h"
#include "Includes.h"
#pragma once
#ifndef TEAM_H
#define TEAM_H
class Team;


class abstr {
protected:
	string name;
public:
	virtual string getName() = 0;
};


class Player :public abstr{
protected:
	string shirtno;
	string average;
	string ranking;
	string totalRun;
	string matches;
	string wickets;
	string type;
public:
	Player(
		string name = " ", string shirtno = "0", string average = "0", string ranking = "0", string totalRun = "0",
		string matches = "0", string wickets = "0", string type = "bowler") {
		this->name = name;
		this->shirtno = shirtno;
		this->average = average;
		this->ranking = ranking;
		this->totalRun = totalRun;
		this->matches = matches;
		this->wickets = wickets;
		this->type = type;
	}
	string getName() {
		return name;
	}
	string getShirtNo() {
		return shirtno;
	}
	string getAverage() {
		return average;
	}
	string getRanking() {
		return ranking;
	}
	string getRuns() {
		return totalRun;
	}
	string getMatch() {
		return matches;
	}
	string getwickets() {
		return wickets;
	}
	string gettype() {
		return type;
	}
	void getfiles(string name, ifstream& file) {
		this->name = name;
//		ifstream file("files/" + name + ".txt");
		getline(file, shirtno, ',');
		getline(file, average, ',');
		getline(file, ranking, ',');
		getline(file, totalRun, ',');
		getline(file, matches, ',');
		getline(file, wickets, ',');
		getline(file, type, ',');
	}
	void update(Player temp,string teamname) {
		if (temp.shirtno != "")this->shirtno = temp.shirtno;
		if (temp.average != "")this->average = temp.average;
		if (temp.ranking != "")this->ranking = temp.ranking;
		if (temp.totalRun != "")this->totalRun = temp.totalRun;
		if (temp.matches != "")this->matches = temp.matches;
		if (temp.wickets != "")this->wickets = temp.wickets;
		if (temp.type != "")this->type = temp.type;

		if (name != "") {
			string filename = { "files/" + teamname + ".txt" };
			removeupdate(filename, this->name, temp.name);
			this->name = temp.name;
		}
		//remove(&filename[0]);
		ofstream file("files/" + this->name + ".txt");
		file  << this->shirtno << "," << this->average << "," <<
			this->ranking << "," << this->totalRun << "," <<
			this->matches << "," << this->wickets << "," << this->type;
		file.close();

	}
	void removeupdate(string filename, string name, string toreplace,bool isnotplayer=false) {
		fstream file;
		string temp="", temp1;
		file.open(filename);

		getline(file, temp1);
		temp += temp1;
		if (!isnotplayer) {
			temp += "\n";
			getline(file, temp1);
			temp += temp1;
		}
		cout << temp << endl;
		file.close();
		//remove(&filename[0]);
		cout << endl << temp.find(name);
		temp.replace(temp.find(name), name.length(), toreplace);
		ofstream file2;//it will create the file and open to write
		file2.open(filename);
		file2 << temp;
		file2.close();
	}
	static void addplayer(Player player, string teamname) {
		ofstream file("files/" + teamname + ".txt", ios::app);

		file << player.name << ",";
		file.close();

		file.open("files/" + player.name + ".txt", ios::out);
		file << player.name << "," << player.shirtno << "," << player.average << "," << player.ranking
			<< "," << player.totalRun << "," << player.matches
			<< "," << player.wickets << "," << player.type;
		file.close();
	}
};
class Team :public abstr{
	string matchWon;
	string matchLost;
	string captain;
	string coach;
	string ranking;
	string username;
	string password;
	friend class UpdateTeam;

public:
	int noofplayers;
	static int size;
	Array<Player> player;
	Team(string name,
		string matchWon,
		string matchLost,
		string captain,
		string coach,
		string ranking,
		string username,
		string password): matchWon(matchWon), matchLost(matchLost), captain(captain),
		coach(coach), ranking(ranking), username(username), password(password){
		this->name = name;
	}
	Team() :player(5, 0) {
		noofplayers = 0;
	}
	void updatecc(string coach = "", string captain = "") {
		string filename = { "files/" + name + ".txt" };

		if (coach != "") {
			player[0].removeupdate(filename, this->coach, coach);
			this->coach = coach;
		}
		if (captain != "") {
			this->captain = captain;
			player[0].removeupdate(filename, this->captain, captain);
		}
	}
	string getName() {
		return name;
	}
	string getcaptain() {
		return captain;
	}
	string getcoach() {
		return coach;
	}
	string getmatchWon() {
		return matchWon;
	}
	string getmatchLost() {
		return matchLost;
	}
	string getranking() {
		return ranking;
	}
	void addPlayer(Player play) {
		Array<Player> player;
		player.append(play);
	}
	bool is_valid(string username, string password) {
		if (username == this->username && password == this->password)  return true;
		return false;
	}
	Player* getplayer(int index) {
		try {
			if (index >= 0 && index < noofplayers)
				return &player[index];
			else throw index;
		}
		catch (int index) {
			return &player[noofplayers - 1];
		}
	}
	void updateteam(Team team) {
		if (team.name != "")this->name = team.name;
		if (team.matchWon != "")this->matchWon = team.matchWon;
		if (team.matchLost != "")this->matchLost = team.matchLost;
		if (team.captain != "")this->captain = team.captain;
		if (team.coach != "")this->coach = team.coach;
		if (team.ranking != "")this->ranking = team.ranking;
		if (team.username != "")this->username = team.username;
		if (team.password != "")this->password = team.password;
	}
	void removeplayer(int index) {
		string filename = { "files/" + player[index].getName() + ".txt" };
		remove(&filename[0]);
		filename = { "files/" + this->name + ".txt" };


		player[index].removeupdate(filename, player[index].getName() + ",", "");
		if (player[index].getName() == captain)
			player[index].removeupdate(filename, player[index].getName() + ",", "");


		noofplayers--;
		player[index] = player[noofplayers];
	}
	int searchPlayer(string name) {
		for (int i = 0; i < player.size; i++) {
			if (player[i].getName().find(name) != -1)
				return i;
		}
		return -1;
	}
	void getfiles(string name, string username, string password,ifstream&file) {
		this->name = name;
		this->username = username;
		this->password = password;
		//cout << "Name1 : " << name << " Username : " << username << " Password : " << password << endl;
		string playername;
		//ifstream file("files/" + name + ".txt");
		getline(file, matchWon, ',');
		getline(file, matchLost, ',');
		getline(file, coach, ',');
		getline(file, captain, ',');
		getline(file, ranking);
		//cout << "matchWon : " << matchWon << " matchLost : " << matchLost << " captain : " << captain<< " ranking : " << ranking << endl;
		cout << username << endl << password << endl;

		while (!file.eof()) {
			getline(file, playername, ',');
			if (!file.eof()) {
				ifstream file2("files/" + playername + ".txt");
				if (file2.good()) {
					player.append(Player());
					player[player.size - 1].getfiles(playername,file2);
					
					file2.close();
				}
			}
		}
		//file.close();
		noofplayers = player.size;
	}
};
//static int Team::size = 0;

#endif // !TEAM_H
