#ifndef GRID_H
#define	GRID_H 

#include "creature.h"
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

class Grid : public sf::Drawable {
	public:
		Grid(int, int);
		
		std::vector<sf::RectangleShape> getRectsToRender(int screenWidth, int screenHeight) const;
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void kill(int);
		void revive(int);
		void toggleByClick(int screenWidth, int screenHeight, int x, int y);
		void toggleState();	
		void update();

	private:
		bool paused;	
		int cols, rows, aliveNeighbors;
		std::vector<Creature> creatures;

	//internal member functions	
		int neighborCount(int index);
		sf::RectangleShape getRect(int screenWidth, int screenHeight, int index)const;
		std::vector<sf::RectangleShape> getGridRects(int screenWidth, int screenHeight) const;	
		void tick();
};

#endif 
