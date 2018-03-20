#include "../include/grid.h"
#include <iostream>

#define ALIVECOLOR sf::Color(0,0,0,255)
#define DEADCOLOR sf::Color(35,0,255,255)

Grid::Grid(int width, int height) : sf::Drawable(), paused(true), cols(width), rows(height){
	for(int i = 0; i < cols*width; i++){
		creatures.push_back(Creature());
	}
}

//overridden member function to draw the grid
void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	auto s = target.getSize();
	int w = s.x, h = s.y;
	std::vector<sf::RectangleShape> rects = getGridRects(w, h);
	for(auto r : rects){
		target.draw(r);
	}
}

void Grid::toggleState(){
	paused = !paused;
}

void Grid::update(){
	if(!paused)
		tick();
}

void Grid::kill(int index){
	creatures[index].m_dead = true;
}

void Grid::revive(int index){
	creatures[index].m_dead = false;
}

//performs all of the rules for GameOfLifeTM
void Grid::tick(){

	int count;
	std::vector<int> killList;
	std::vector<int> reviveList;
	//calculate neighbors and put each cell into kill/revive lists	
	for(int i = 0; i < creatures.size(); i++){
		count = neighborCount(i);
		//live cell has 3 alive neighbors
		if(creatures[i].alive() && (count > 3 || count < 2) ){
			killList.push_back(i);
		}
		//dead cells has 3 live neighbors
		else if(creatures[i].dead() && count == 3){
			reviveList.push_back(i);
		}

	}
	//after processing all cells:
	
	//kill under/overpopulated cells
	for(int i : killList){
		kill(i);	
	}
	//revive cells that deserve a second chance at life
	for(int i : reviveList){
		revive(i);	
	}

}

int Grid::neighborCount(int index){
	int count = 0;
	//topleft, topmiddle topright right bottomright bottommiddle bottomleft left 
	int TL, TM, TR, R, BR, BM, BL, L;
	//set neighbor candidates	
	TM = index - cols;
	TL = TM - 1;
	TR = TM + 1;
	R = index + 1;
	BM = index + cols;
	BR = BM + 1;
	BL = BM -1;
	L = index - 1;
	//resolve bad neighbor candidates
	if(index%cols == 0){
		//The index hugs the left side of the grid
		TL = -1;	//nullify
		L = -1;
		BL = -1;
	}
	if(index%cols == cols-1){
		//the index hugs the right side of the grid
		TR = -1;
		R = -1;
		BR = -1;

	}

	if(index/cols == 0){
		//the index hugs the top of the grid
		TL = -1;
		TM = -1;
		TR = -1;
	}
	if(index/cols == cols-1){
		//the index hugs the bottom of the grid
		BL = -1;
		BM = -1;
		BR = -1;
	}
	//increment the count for each valid neighbor that is alive
	if(TL != -1 && creatures[TL].alive())
		count++;
	if(TR!= -1 && creatures[TR].alive())
		count++;
	if(TM != -1 && creatures[TM].alive())
		count++;
	if(BL != -1 && creatures[BL].alive())
		count++;
	if(L != -1 && creatures[L].alive())
		count++;
	if(R != -1 && creatures[R].alive())
		count++;
	if(BR != -1 && creatures[BR].alive())
		count++;
	if(BM != -1 && creatures[BM].alive())
		count++;
	
	return count;
}

std::vector<sf::RectangleShape> Grid::getGridRects(int screenWidth, int screenHeight) const{
	std::vector<sf::RectangleShape> rects;
	for(int i = 0; i < creatures.size(); i++){
		auto rect = getRect(screenWidth, screenHeight, i);
		rect.setOutlineThickness(1.0);
		
		//if set creature color based on life/death
		if(creatures[i].alive()){
			rect.setFillColor(ALIVECOLOR);	
		}
		else{
			rect.setFillColor(DEADCOLOR);
		}

		rects.push_back(rect);
	}
	return rects;
}

//returns a properly sized and positioned drawable rectangle
sf::RectangleShape Grid::getRect(int screenWidth, int screenHeight, int index) const {
	sf::RectangleShape rect;
	int w = screenWidth/cols;
	int h = screenHeight/rows;		//Create a drawable rectangle for specific cell	
	int x = w*(index%cols);
	int y =	h*(index/cols);	
	rect.setSize(sf::Vector2f(w,h));
	rect.setPosition(x,y);
	return rect;
}

void Grid::toggleByClick(int screenWidth, int screenHeight, int x, int y){
	//use mouse coordinates (x,y) to detect which cell was clicked, then toggle the cells state	
	int colNumber = x/(screenWidth/cols);
	int rowNumber = y/(screenHeight/rows);
	creatures[rowNumber*rows + colNumber].m_dead = !creatures[rowNumber*rows+colNumber].m_dead;
}
