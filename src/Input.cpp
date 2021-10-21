#include <Input.hpp>
#include <Program.hpp>


void handle_global_input(sf::Event& event, Program& p){
	// User clicked the windows close button
	if (event.type == sf::Event::Closed){
		p.running = false;
		return;

	} else if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){

		case sf::Keyboard::Space:
			break;


		case sf::Keyboard::Escape: // back out / end program
			break;
		}
	}
}






