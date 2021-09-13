#include "Includes.h"

#pragma once
#ifndef WORLDRECORD_H
#define WORLDRECORD_H

class WorldRecord{
	RectangleShape shape;
	Text text;
	Text text1;
public:
	WorldRecord(){}
	WorldRecord(string var, string var1, int x, int y, int width, int height) {
		shape.setSize(Vector2f(width, height));
		shape.setPosition(x, y);
		shape.setFillColor(Color(45, 56, 73));

		text.setFont(realfont);
		text.setString(var);
		text.setCharacterSize(17);
		text.setPosition(shape.getPosition().x, shape.getPosition().y);
		text.setFillColor(Color::White);

		text1.setFont(realfont);
		text1.setString(var1);
		text1.setCharacterSize(17);
		text1.setPosition(shape.getPosition().x + width + 10, shape.getPosition().y + 5);
		text1.setFillColor(Color(45, 56, 73));
	}
	void setposition(Vector2f pos, Vector2f size = { 140,30 }) {
		shape.setPosition(pos);
		shape.setSize(size);
		text.setPosition(pos);
		text1.setPosition(pos.x + shape.getSize().x + 10, pos.y + 5);
	}
	
	void display(RenderWindow& window) {
		window.draw(shape);
		window.draw(text);
		window.draw(text1);
	}


	
};

class News {
	string name;
	Text text,text1;
	RectangleShape shape;
public:
	News() {};
	News(string var,string var1,int x, int y, int z, int h, int i, int j, int k, int m, int n) {
		name = var;
		shape.setSize(Vector2f(z, h));
		shape.setPosition(x, y);
		shape.setFillColor(Color(45, 56, 73));
		text.setFont(realfont);
		text.setString(var);
		text.setCharacterSize(z - k);
		text.setPosition(shape.getPosition().x + i, shape.getPosition().y + j);
		text.setFillColor(Color::White);

		text1.setFont(realfont);
		text1.setString(var1);
		text1.setPosition(shape.getPosition().x+x,shape.getPosition().y+ y);
		text1.setFillColor(Color(45,56,73));
		text1.setPosition(shape.getPosition().x + m, shape.getPosition().y + n);
	}

	

	void display(RenderWindow& window) {
		window.draw(shape);
		window.draw(text);
		window.draw(text1);
	}

	
};

class WorldRecords {
	Array<WorldRecord> worldrecord;
	Array<News> news;
	bool isnews;
public:
	WorldRecords(bool isnews = false):isnews(isnews) {
		string data[] = { "World Records" ,"Most Runs" ,"Runs" ,"Highest Score" ,"Score" ,"Most Sixes" ,"sixes",
		"Most Fours" ,"fours","Centuries", "Num", "Average_Bat", "Average", "Most Wickets" ,"Wickets"};
		string data2[15], data3[5];
		getdata(data2,data3);
		for (int i = 0; i < 15; i++) {
			worldrecord.append(WorldRecord(data[i], data2[i], 635, 80, 160, 30));
		}
		for (int i = 1; i < 15; i++) {
			if (i % 2 == 1) {
				worldrecord[i].setposition(Vector2f(320, 150 + (i-1) * 30));
			}
			else {
				worldrecord[i].setposition(Vector2f(900, 150 + (i-2) * 30));
			}
		}
		news.append(News("News", "", 620, 80, 210, 50, 65, 5, 180, 0, 0));
		for (int i = 0; i < 5; i++) {
			news.append(News("", data3[i], 620, 150 + i * 80, 0, 0, 1, 5, 180, -300, 30));
		}
	}
	
	void getdata(string* arr,string*arr2) {
		arr[0] = "";
		fstream file;
		file.open("files/World Record.txt");
		for (int i = 1; i < 15; i++) {
			getline(file, arr[i], ',');
		}
		file.close();

		file.open("files/News.txt");

		for (int i = 0; i < 5; i++) {
			getline(file, arr2[i], ',');
		}
		file.close();
	}
	void display(RenderWindow& window) {
		
		if (state==State1::worldrecords) {
			for (int i = 0; i < 15; i++) {
				worldrecord[i].display(window);
			}
		}
		else {
			for (int i = 0; i < 6; i++) {
				news[i].display(window);
			}
		}
	}
};

#endif // !WORLDRECORD_H