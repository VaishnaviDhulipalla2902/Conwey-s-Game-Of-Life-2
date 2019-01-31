#include "Grid.h"

#ifndef SuperGrid_H_
#define SuperGrid_H_

#include <iostream>

class SuperGrid{
    public:
        
        SuperGrid();
        SuperGrid(int NR,int NC,int gridRows,int gridColumns,int k,int s) ; // constructor 
        ~SuperGrid() ; // destructor 
        SuperGrid(const SuperGrid&) ; // copy constructor
        //friend function
        friend std::ostream& operator<< (std::ostream &, SuperGrid &) ;

        //getters
        int getRows(){
            return NR;
        }
        int getColums(){
            return NC;
        }
        Grid** getGrids(){
            return grids;
        }

        //setters
        void setRows(int NR);
        void setColumns(int NC);
        void setGrids(Grid** grids);

        //public functions
        void generate_initial_state();
        void update_neighbourhood();
        void update_grid();
        void print_grid();
        int update_Supergrid();
        void synchronizeSuperGrid();
        void updateGrids();
        int count_total_neighbours(){
            int sum = 0;
            for(int i=0;i<NR;i++){
                for(int j=0;j<NC;j++){
                    int num = grids[i][j].count_live_neighbours();
                    sum += num;
                }
            }
            return sum;
        }
        int isValid(Grid** gridsNew){
            for(int i=0;i<NR;i++){
                if(gridsNew[i][0].getState() != '0' || gridsNew[i][NC-1].getState() != '0') return 0;
            }
            for(int i=0;i<NC;i++){
                if(gridsNew[0][i].getState() != '0' || gridsNew[NR-1][i].getState() != '0') return 0;
            }
            return 1;
        }
    private:
        Grid** grids;
        int NR,NC,gridRows,gridColumns,k,s;
    
};

#endif