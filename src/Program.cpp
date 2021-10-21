#include <Program.hpp>
#include <Entity.hpp>
#include <Text.hpp>
#include <Image.hpp>
#include <Speaker.hpp>
#include <Stack.hpp>
#include <Shapes.hpp>
#include <Input.hpp>
#include <TextField.hpp>
#include <Trie.hpp>
#include <filesystem>

namespace fs = std::filesystem;




Program::Program() {
	// setup any static members
	aud::load_all(); // load all the program sounds
	load_fonts();

	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	window_ptr = new sf::RenderWindow(sf::VideoMode(WINW, WINH), "RootScout", sf::Style::Titlebar | sf::Style::Close, settings);
	window_ptr->setFramerateLimit(60);

	// UI entities
	main_tbox = new TextField({0, 25, WINW, 50}, "");


	// fps counter
	fps = sf::Text("0", FONT_LIBMONO, 30);
	sf::FloatRect bounds = fps.getLocalBounds();
	fps.setPosition(20, WINH - bounds.height - bounds.top - 5);
	fps.setFillColor(JB_GREEN);

	// grid lines
	float grid_line_thickness = 2;
	auto yaxis = new LineShape({CENTER_WIN_X, CENTER_WIN_Y, grid_line_thickness, WINH});
	auto xaxis = new LineShape({CENTER_WIN_X, CENTER_WIN_Y, WINW, grid_line_thickness});


	draw_list = {
		main_tbox
	};

	engage_with(main_tbox);


	// Fill the trie
	std::set<std::string> ignored_ext = {".o"};

	for (const auto& entry : fs::recursive_directory_iterator(".")){
		fs::path p = entry.path();
		if (not_in(p.extension(), ignored_ext)){
			std::string fname = jb::lowercase(p.filename());
			std::string path_from_root = p.relative_path();
			trie.push( {fname, path_from_root} );
		}
	}

}


void Program::engage_with(Entity *ent){
	if (engaged_entity){
		engaged_entity->engage(false); // disengage current entity
	}
	last_engaged = engaged_entity;
	engaged_entity = ent;
	engaged_entity->engage(true);
}


void Program::cleanup(){
	// cleanup up resources
	TextField::cleanup();
	aud::cleanup();

	delete window_ptr;
}


void Program::prepare_quit(bool _saving){
	saving = _saving;
	running = false;
}



void Program::quit(){
	//
	// Close the program window and clean up heap
	//
	window_ptr->close(); // close window
	cleanup();
}




void Program::update_frame(float dt){
	// update UI entities
	for (Entity *ent : draw_list){
	   ent->update(dt);
	}
	
	// framerate
	static int count = 0;
	char c[6];
	sprintf(c, "%d", (int)(1/dt));
	if (count++ == 25){
		fps.setString(sf::String(std::string(c)));
		count = 0;
	}
}


void Program::draw_frame(sf::RenderWindow& window){
	for (sf::Drawable *ent : draw_list){
		window.draw(*ent);
	}

	//framerate
	//window.draw(fps);
}




void Program::mainloop(){
	//
	// Main program loop
	//

	sf::RenderWindow& window = *(window_ptr);
	sf::Clock clock;

	while (running && window.isOpen()) {
		window.clear(JBC_BG); // clear last frame and set bg color

		bool event_processed = false;
		sf::Event event;

		while (window.pollEvent(event)) {
			// @NOTE: A single character keystroke produces both a KeyPressed and a TextEntered event; be aware of that.
			// @NOTE: keystrokes shared by the current entity and the universals should prioritize the entity.
			// So entity handlers should be called first.
			
			// @FIXME: some events are processed by both the entity and the global handler.
			if (!event_processed)
				event_processed = engaged_entity->handler(event, *this);
			if (!event_processed)
				handle_global_input(event, *this);

		}
		// all inputs polled for this frame

		update_frame( clock.restart().asSeconds() );
		draw_frame(window);


		window.display(); // display completed frame
	}
}



