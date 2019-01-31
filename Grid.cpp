#include "Grid.h"
#include <stdlib.h>
#include <time.h>
#include<iostream>
#include "Gridcell.h"

using namespace std;


Grid::Grid(){}

Grid::Grid(int r,int c,int x,int y):rows(r),columns(c),x(x),y(y){
	gridcells = new Gridcell*[rows] ;
    for (int i = 0 ; i < rows ; i++) {
        gridcells[i] = new Gridcell[columns] ;
	}
	for(int i=0;i<8;i++){
        neighbourhood[i] = '0';
    }
}

Grid::~Grid(){
    for(int i=0;i<rows;i++){
        delete[] gridcells[i];
    }
    delete[] gridcells;
    rows = 0;
    columns = 0;
}

Grid::Grid(const Grid& G):rows(G.rows),columns(G.columns){
    gridcells = new Gridcell*[rows] ;
    for (int i = 0 ; i < rows ; i++) 
        gridcells[i] = new Gridcell[columns] ;
    
    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < columns; j++) 
	        gridcells[i][j] = G.gridcells[i][j];
}


// Setters
void Grid::setRows(int r){
    rows = r;
}

void Grid::setColumns(int c){
    columns = c;
}

void Grid::setGridcells(Gridcell** cells){
    
    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < columns; j++) 
	        gridcells[i][j] = cells[i][j];

	this->update_neighbourhood();
}
void Grid::setX(int x1){
    x = x1;
}

void Grid::setY(int y1){
    y = y1;
}

void Grid::setState(unsigned char s){
    state = s;
    return;
}

void Grid::setNeighbourhood(unsigned char* newNeighbourhood){
    for(int i=0;i<8;i++){
        neighbourhood[i] = newNeighbourhood[i];
    }
    return;
}


// Functions
void Grid::generate_initial_state(unsigned char state){

	if(state=='1'){
		for(int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){
				gridcells[i][j].setX(i);
				gridcells[i][j].setY(j); 
				gridcells[i][j].setState('0');
				deadCount++;
			}
		}
		liveCount = 0;
		this->makeAlive();
	}
	else{
		for(int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){
				if(i==0 || j==0 || i==rows-1 || j==columns-1){
					gridcells[i][j].setX(i);
					gridcells[i][j].setY(j); 
					gridcells[i][j].setState('0');
				}
				else{
					gridcells[i][j].setX(i);
					gridcells[i][j].setY(j); 
					gridcells[i][j].setState('1');
					liveCount++;
				}
			}
		}
		deadCount = columns*2 + (rows-2)*2;
		this->makeDead();
	}
	
}

void Grid::update_neighbourhood(){
    unsigned char neighbourhood[8];
    for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			if(j!=columns-1)neighbourhood[0] = gridcells[i][j+1].getState();
			else neighbourhood[0] = '0';
			if(j!=columns-1 && i!=0)neighbourhood[1] = gridcells[i-1][j+1].getState();
			else neighbourhood[1] = '0';
			if(i!=0)neighbourhood[2] = gridcells[i-1][j].getState();
			else neighbourhood[2] = '0';
			if(j!=0 && i!=0)neighbourhood[3] = gridcells[i-1][j-1].getState();
			else neighbourhood[3] = '0';
			if(j!=0)neighbourhood[4] = gridcells[i][j-1].getState();
			else neighbourhood[4] = '0';
			if(j!=0 && i!=rows-1)neighbourhood[5] = gridcells[i+1][j-1].getState();
			else neighbourhood[5] = '0';
			if(i!=rows-1)neighbourhood[6] = gridcells[i+1][j].getState();
			else neighbourhood[6] = '0';
			if(j!=columns-1 && i!=rows-1)neighbourhood[7] = gridcells[i+1][j+1].getState();
			else neighbourhood[7] = '0';
			gridcells[i][j].setNeighbourhood(neighbourhood);
		}
	}
}

void Grid::makeAlive(){
	int livePercent = (liveCount*100)/(rows*columns);
	int reqLiveCells = (0.50 - livePercent/100)*(rows*columns);
	for(int i=0;i<reqLiveCells;){
		int x = rand()%(rows-2) + 1;
		int y = rand()%(columns-2) + 1;	
		if(gridcells[x][y].getState()=='0'){
			gridcells[x][y].setState('1');
			liveCount++;
			deadCount--;
			i++;
		}		
	}
    state = '1';
	this->update_neighbourhood();	
}

void Grid::makeDead(){
	
	int deadPercent = (deadCount*100)/(rows*columns) ;	
	int reqDeadCells = (0.50 - deadPercent/100)*rows*columns;	
	for(int i=0;i<reqDeadCells;){
		int x = rand()%(rows-2) + 1;
		int y = rand()%(columns-2) + 1;	
		if(gridcells[x][y].getState()=='1'){
			gridcells[x][y].setState('0');
			deadCount++;
			liveCount--;
			i++;
		}
	}
	state = '0';
	this->update_neighbourhood();
}

void Grid::getNextGenerations(int numOfGenerations){
	int isValid = this->isValid(this->gridcells);
	if(isValid){
		for(int i=0;i<numOfGenerations;i++){
			isValid = this->update_grid();
			if(!isValid) return ;
			generation++;
		}
	}
}

int Grid::update_grid(){
    Gridcell** proxy = new Gridcell*[rows] ;
    for (int i = 0 ; i < rows ; i++) 
        proxy[i] = new Gridcell[columns] ;
	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			int num = gridcells[i][j].count_live_neighbours();
			if(gridcells[i][j].getState()-'0'==0){
				if(num==3){
					proxy[i][j].setState ('1');
					liveCount++;
					deadCount--;
				}
				else{
					proxy[i][j]. setState ('0');
				}
			}
			else{
				if(num==2 || num==3){
					proxy[i][j].setState('1');
				}
				else{
					proxy[i][j].setState('0');
					deadCount++;
					liveCount--;
				}
			}
		}
	}
	int isValid = this->isValid(proxy);
	if(isValid){
		livePercent = (liveCount*100)/(rows*columns);
		deadPercent = (deadCount*100)/(rows*columns);
		if(livePercent >= 50) state = '1';
		else state = '0';
		this->setGridcells(proxy);
		return 1;
	}
	else{
		return 0;
	}
}


//friend function
void Grid::print_grid(){
    for(int j=0;j<rows;j++){
        for(int k=0;k<columns;k++){
			printf("%c ",gridcells[j][k].getState());
        }
        std:: cout<<"\n";
    }
    std:: cout<<"\n";
};

// Friend functions
std::ostream& operator<<(std::ostream& os, Grid& g) {

	for(int j=0;j<g.rows;j++){
        for(int k=0;k<g.columns;k++){
			if(g.gridcells[j][k].getState() == '0') os << "o ";
			else os << "+ ";
        }
        os << std::endl;
    }
	os << std :: endl;
  	return os;
}

Grid& Grid::operator= (const Grid & grid)
{
    rows = grid.rows;
	columns = grid.columns;
	gridcells = new Gridcell*[rows] ;
    for (int i = 0 ; i < rows ; i++) {
        gridcells[i] = new Gridcell[columns] ;
		for(int j=0;j<columns;j++) {
			gridcells[i][j] = grid.gridcells[i][j];
			gridcells[i][j].setX(i);
			gridcells[i][j].setY(j);
		}
	}
	x = grid.x;
	y = grid.y;
	for(int i=0;i<8;i++){
		neighbourhood[i] = grid.neighbourhood[i];
	}
	state = grid.state;
	liveCount = grid.liveCount;
	deadCount = grid.deadCount;
    // return the existing object so we can chain this operator
    return *this;
}



