#include"Includes.h"
#include "Array.h"
#pragma once

#ifndef MATCHES_H
#define MATCHES_H

class Matches
{
	Text headings[8];
	Text** matches;
	int noofmatches;
	
public:
	Matches(Vector2f pos = { 200,200 }) {
		string temp;
		noofmatches = noofline();
		cout << noofmatches << endl << endl << endl;
		ifstream file;
		file.open("files/matches.txt");
		string data[] = { "Team1","Team2","Date","Venue","Type","Comentator","Umpire","Status" };
		for (int i = 0; i < 8; i++) {
			headings[i] = Text(data[i], realfont, 20);
			headings[i].setPosition(Vector2f(304 + i * 120, 100));
			headings[i].setFillColor(Color(45, 56, 73));
			headings[i].setStyle(Text::Bold | Text::Italic);
		}
		headings[4].setPosition(Vector2f(304 + 4 * 130, 100));
		headings[7].setPosition(Vector2f(1120, 100));

		if (file.good()) {
			matches = new Text * [noofmatches];
			for (int i = 0; noofmatches && !file.eof(); i++) {
				matches[i] = new Text[8];

				for (int j = 0; j < 8 && !file.eof(); j++) {
					if (i > 0 && j == 0)file.ignore();
					getline(file, temp, ',');
					matches[i][j] = Text(temp, realfont, 16);
					matches[i][j].setPosition(Vector2f(304 + j * 120, 150 + i * 40));
					matches[i][j].setFillColor(Color::Black);
				}
				matches[i][4].setPosition(Vector2f(304 + 4 * 130, 150 + i * 40));
				matches[i][7].setPosition(Vector2f(1120, 150 + i * 40));
			}
		}
		file.close();
	}
	int noofline() {
		string temp; int i = 0;
		ifstream file;
		file.open("files/matches.txt");

		while (!file.eof()) {
			getline(file, temp);
			i++;
		}
		file.close();
		return i - 1;
	}

	
	
	void display(RenderWindow &window) {

		for (int i = 0; i < 8; i++) {
			window.draw(headings[i]);
		}
		for (int i = 0; i < noofmatches; i++) {
			for (int j = 0; j < 8; j++) {
				window.draw(matches[i][j]);
			}
		}
	}
};


#endif // !MATCHES_H