#ifndef grid
#define grid
#include "creature.h"
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
class Grid : public sf::Drawable{
	public:
		Grid(int, int);
		void update();
		void toggleState();	
		std::vector<sf::RectangleShape> getRectsToRender(int screenWidth, int screenHeight) const;
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void toggleByClick(int screenWidth, int screenHeight, int x, int y);
		void kill(int);
		void revive(int);
	private:
		bool paused;	
		void tick();
		int neighborCount(int index);
		sf::RectangleShape getRect(int screenWidth, int screenHeight, int index)const;
		std::vector<sf::RectangleShape> getGridRects(int screenWidth, int screenHeight) const;	
		std::vector<Creature> creatures;
		int cols, rows, aliveNeighbors;
};

#endif 
