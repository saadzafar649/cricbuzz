#include "Includes.h"
#pragma once
#ifndef GETTEXT_H
#define GETTEXT_H

class GetText;
class GetText :public Text {
protected:
	int limit;
	string str;
public:
	GetText(int limit=10):limit(limit) {
		str = "";
		setFillColor(Color::Green);
		
		setFont(realfont);
	}
	void emptystr() {
		str = "";
	}
	bool update(Event& event) {
		if (str.length() != limit || event.key.code == Keyboard::BackSpace) {
			str = Keytochar(event.key.code, str);
			setString(str);
			return true;
		}
		return false;
	}
	//string getstring() {
	//	return str;
	//}
	static string Keytochar(Keyboard::Key& key, string str) {
		char last = ' ';
		if (key >= 0 && key < 26)
			last = static_cast<char>(key + 65);//0+65=Ascii of A
		else if (key >= 26 && key < 36)
			last = static_cast<char>(key + 22);//26+22=48 Ascii of 0
		else if (key == 50)last = '.';
		else if (key == 52)last = '/';
		else if (key == Keyboard::Space)
			last = ' ';
		else if (key == Keyboard::Return)
			last = '\n';
		else if (key == Keyboard::BackSpace) {
			if (str != "")
				str.pop_back();
			return str;
		}
		str += last;
		return str;
	}
};

#endif // !GETTEXT_H