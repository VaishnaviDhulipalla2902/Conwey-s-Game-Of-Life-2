#include "SuperGrid.h"
#include <stdlib.h>
#include <time.h>
#include<iostream>

using namespace std;

SuperGrid::SuperGrid(){}

SuperGrid::SuperGrid(int r,int c,int rows,int columns,int k,int s):NR(r),NC(c),gridColumns(columns),gridRows(rows),k(k),s(s){

	grids = new Grid*[NR] ;
    for (int i = 0 ; i < NR ; i++) {
		grids[i] = new Grid[NC];
        for(int j=0; j < NC; j++)
			grids[i][j] = Grid(NR,NC,i,j);
	}
}

SuperGrid::~SuperGrid(){
    for(int i=0;i<NR;i++){
        delete[] grids[i];
    }
    delete[] grids;
    NR = 0;
    NC = 0;
}

SuperGrid::SuperGrid(const SuperGrid& S):NR(S.NR),NC(S.NC),gridColumns(S.gridColumns),gridRows(S.gridRows),k(S.k),s(S.s){
    grids = new Grid*[NR] ;
    for (int i = 0 ; i < NR ; i++) 
        grids[i] = new Grid[NC] ;
    
    for (int i = 0; i < NR; i++) 
        for (int j = 0; j < NC; j++) 
	        grids[i][j] = S.grids[i][j];
}

void SuperGrid::setRows(int rows){
    NR = rows;
}

void SuperGrid::setColumns(int columns){
    NC = columns;
}

void SuperGrid::setGrids(Grid** newGrids){
    
    for (int i = 0; i < NR; i++) 
        for (int j = 0; j < NC; j++) 
	        grids[i][j] = newGrids[i][j];
}


void SuperGrid::update_neighbourhood(){
    unsigned char neighbourhood[8];
    for(int i=0;i<NR;i++){
		for(int j=0;j<NC;j++){
			if(j!=NC-1)neighbourhood[0] = grids[i][j+1].getState();
			else neighbourhood[0] = '0';
			if(j!=NC-1 && i!=0)neighbourhood[1] = grids[i-1][j+1].getState();
			else neighbourhood[1] = '0';
			if(i!=0)neighbourhood[2] = grids[i-1][j].getState();
			else neighbourhood[2] = '0';
			if(j!=0 && i!=0)neighbourhood[3] = grids[i-1][j-1].getState();
			else neighbourhood[3] = '0';
			if(j!=0)neighbourhood[4] = grids[i][j-1].getState();
			else neighbourhood[4] = '0';
			if(j!=0 && i!=NR-1)neighbourhood[5] = grids[i+1][j-1].getState();
			else neighbourhood[5] = '0';
			if(i!=NR-1)neighbourhood[6] = grids[i+1][j].getState();
			else neighbourhood[6] = '0';
			if(j!=NC-1 && i!=NR-1)neighbourhood[7] = grids[i+1][j+1].getState();
			else neighbourhood[7] = '0';
			grids[i][j].setNeighbourhood(neighbourhood);
		}
	}
}

void SuperGrid::generate_initial_state(){
	for(int i=0;i<NR;i++){
		for(int j=0;j<NC;j++){
			if(i==0 || i==NR-1 || j==0 || j==NC-1){
				grids[i][j].generate_initial_state('0');
			}
			else{
				int num =NR*i+j;
				if(num%2==0) grids[i][j].generate_initial_state('1');
				else grids[i][j].generate_initial_state('0');	
			}
		}
	}
	this->update_neighbourhood();
}

void SuperGrid::updateGrids(){
	for(int i=0;i<NR;i++){
		for(int j=0;j<NC;j++){
			grids[i][j].getNextGenerations(k);
		}
	}
}

int SuperGrid::update_Supergrid(){

    Grid** proxy = new Grid*[NR] ;
    for (int i = 0 ; i < NR ; i++) {
		proxy[i] = new Grid[NC];
		for (int j=0; j<NC; j++)
			proxy[i][j] = grids[i][j];
	}
	for(int i=0;i<NR;i++){
		for(int j=0;j<NC;j++){
			
			int num = grids[i][j].count_live_neighbours();
			if(grids[i][j].getState()-'0'==0){
				if(num==3) proxy[i][j].makeAlive();
				
			}
			else{				
				if(num!=2 && num!=3){
					proxy[i][j].makeDead();
				}
			}
		}
	}
	int isValid = this->isValid(proxy);
	if(isValid){
		this->setGrids(proxy);
		this->update_neighbourhood();
		return 1;
	}
	else{
		return 0;
	}
}

void SuperGrid::synchronizeSuperGrid(){
	for(int i=0;i<s;i++){
		this->updateGrids();
		cout << *this;
		int isValid = this->update_Supergrid();
		if(!isValid) return;
		cout << *this;
	}
}


// Friend functions //
std::ostream& operator<<(std::ostream& os, SuperGrid& S) {	
	for(int i=0;i<S.NR;i++){
		for(int l=0;l<S.gridRows;l++){
			for(int j=0;j<S.NC;j++){
				for(int k=0;k<S.gridColumns;k++){
					if(S.grids[i][j].getGridcells()[l][k].getState()=='0') os<<"o";
					else os<<"+";
				}	
				os << " ";
			}
			os << endl;
		}
		os << endl;
	}
	os << "------------------------------------------" << endl;
  	return os;
}
