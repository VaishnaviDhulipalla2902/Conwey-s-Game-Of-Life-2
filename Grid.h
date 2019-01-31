#include "Gridcell.h"

#ifndef Grid_H_
#define Grid_H_

#include <iostream>

class Grid{
    public:
    
        Grid();
        Grid(int rows,int columns,int x,int y) ; // constructor 
        ~Grid() ; // destructor 
        Grid(const Grid&) ; // copy constructor 
        //friend function
        friend std::ostream& operator<< (std::ostream &, Grid &) ;
        //overloaded assignment operator
        Grid& operator= (const Grid &);

        //getters
        int getRows(){
            return rows;
        }
        int getColumns(){
            return columns;
        }
        unsigned char getState(){
            return state;
        }
        Gridcell** getGridcells(){
            return gridcells;
        }

        //setters
        void setRows(int rows);
        void setColumns(int columns);
        void setGridcells(Gridcell** cells);
        void makeAlive();
        void makeDead();
        void setX(int x);
        void setY(int y);
        void setState(unsigned char state) ;

        //public functions
        void generate_initial_state(unsigned char state);
        void update_neighbourhood();
        int update_grid();
        void print_grid();
        void setNeighbourhood(unsigned char* neighbourhood);
        void getNextGenerations(int numOfGenerations);
        int getGeneration(){return generation;}
        int count_total_neighbours(){
            int sum = 0;
            for(int i=0;i<rows;i++){
                for(int j=0;j<columns;j++){
                    int num = gridcells[i][j].count_live_neighbours();
                    sum += num;
                }
            }
            return sum;
        }
        int isValid(Gridcell** gridCells){
            for(int i=0;i<rows;i++){
                if(gridCells[i][0].getState() != '0' || gridCells[i][columns-1].getState() != '0') return 0;
            }
            for(int i=0;i<columns;i++){
                if(gridCells[0][i].getState() != '0' || gridCells[rows-1][i].getState() != '0') return 0;
            }
            return 1;
        }
        int count_live_neighbours(){
            int count = 0;
            for(int i=0;i<8;i++){
                if(neighbourhood[i]-'1'==0) count++;
            }
            return count;
        }
    private:
        Gridcell** gridcells;
        int rows,columns,livePercent,deadPercent,x,y,generation,liveCount=0,deadCount=0;
        unsigned char state;
        unsigned char neighbourhood[8];
    
};

#endif