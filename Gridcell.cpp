#include "Gridcell.h"
#include<stdio.h>

Gridcell::Gridcell(){}

Gridcell::Gridcell(int x,int y,unsigned char state) : x(x), y(y), state(state) {}

Gridcell::~Gridcell(){
    x = 0;
    y = 0;
    state = '0';
}

Gridcell::Gridcell(const Gridcell &G) : x(G.x),y(G.y),state(G.state){
    for(int i=0;i<8;i++){
        neighbourhood[i] = G.neighbourhood[i];
    }
}

//setters
void Gridcell::setState(unsigned char s){
    state = s;
    return;
}

void Gridcell::setNeighbourhood(unsigned char* newNeighbourhood){
    for(int i=0;i<8;i++){
        neighbourhood[i] = newNeighbourhood[i];
    }
    return;
}

void Gridcell::setX(int x1){
    x = x1;
}

void Gridcell::setY(int y1){
    y = y1;
}




