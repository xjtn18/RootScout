#pragma once
#include <SFML/System.hpp>
#include <functional>
#include <cmath>

#include <jb.hpp>
#include <Trie.hpp>


// FD's
struct Entity;
struct VStack;
struct HStack;
struct LineShape;
struct BorderedRect;
struct TextField;



struct Program {
	bool running = true,
		saving = false;

	// window
	sf::RenderWindow *window_ptr;


	// UI entities
	TextField *main_tbox;
	VStack *section_stack;
	sf::Text fps;
	Entity *engaged_entity = nullptr;
	Entity *last_engaged = nullptr;


	// program state
	std::vector<Entity*> draw_list;
	FileTrie trie;


	// sectors
	int padding;


	Program();
	void prepare_quit(bool _saving);
	void quit();
	void cleanup();
	void engage_with(Entity *ent);
	void update_frame(float dt);
	void draw_frame(sf::RenderWindow& window);
	void mainloop();

};


