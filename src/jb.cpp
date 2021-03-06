#include <jb.hpp>
#include <stdarg.h>


const jb::Transform jb::Transform::Zero = {0,0,0,0};
const char* jb::rootPath = nullptr;

// Window parameters
const float WINW = 400;
const float WINH = 400;

// Fonts
sf::Font FONT_LIBMONO;
sf::Font FONT_LIBMONO_B;

#define _LOAD_TTF(font) font.loadFromFile("res/fonts/" + (std::string)#font + ".ttf")
// '#' is a stringify preproc command: returns string representation of the variable name

void load_fonts() {
	// macro expects font file base name and font variable name to be equivalent
	_LOAD_TTF(FONT_LIBMONO);
	_LOAD_TTF(FONT_LIBMONO_B);
}

// Colors
const sf::Color JB_GREEN     = sf::Color(108, 161, 59);
const sf::Color JB_RED       = sf::Color(255, 101, 74);
const sf::Color JB_WHITE     = sf::Color(229, 240, 225);
const sf::Color JBC_BG       = sf::Color(30, 34, 36);



const jb::Time jb::current_time(){
	std::time_t sinceEpoch = std::time(nullptr);
	std::tm t = *std::localtime(&sinceEpoch);
	return jb::Time(t.tm_hour, t.tm_min);
}


// takes path string literal and returns it sans tail
const char* jb::rtrim(const char* s, size_t len, const char target){
	size_t i = len-1;
	for (; i >= 0; i--){
		if (s[i] == target){ break; }
	}
	if (i < 0){ // tail is entire path
		return s;
	}
	char* res = new char[i+1];
	strncpy(res, s, i);
	res[i] = '\0';
	return res;
}


const char* jb::get_resource(const char* filename){
	char* pth = new char[100];
	std::strcpy(pth, jb::rootPath);
	std::strcat(pth, "/res/");
	std::strcat(pth, filename);
	return pth;
}


const char* jb::get_image(const char* filename){
	char* pth = new char[100];
	std::strcpy(pth, jb::rootPath);
	std::strcat(pth, "/res/images/");
	std::strcat(pth, filename);
	return pth;
}


std::string jb::lowercase(std::string data){
	auto asciitolower = [&](char in) -> char {
		return (in <= 'Z' && in >= 'A') ? in - ('Z' - 'z') : in;
	};
	std::transform(data.begin(), data.end(), data.begin(), asciitolower);
	return data;
}



