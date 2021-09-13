

#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>



using namespace std;
using namespace sf;

#pragma once
enum class State1 {
	teams,
	matches,
	searchplayer,
	worldrecords,
	news,
	loginState,
};
static State1 state;
static Font realfont;