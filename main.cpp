#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#define TITLE "Game of Life"
#include <iostream>
#include "include/grid.h"

using namespace std;


int main(){
	int width = 600, height = 600;
	sf::RenderWindow window(sf::VideoMode(width,height), "Game of Life");
	Grid mainGrid(width/15, height/15);	

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			
			//close window: exit
			if(event.type == sf::Event::Closed){
				window.close();
			}
			else if(event.type == sf::Event::MouseButtonPressed){
				mainGrid.toggleByClick(width, height, event.mouseButton.x, event.mouseButton.y);
			}
			else if(event.type == sf::Event::KeyPressed){
				if(event.key.code == sf::Keyboard::Space)
					mainGrid.toggleState();
			}
			
		}
		window.clear(sf::Color(255,0,255,0));
		mainGrid.update();
		window.draw(mainGrid);	
			
		window.display();
		sf::sleep(sf::milliseconds(200));
	}
}

