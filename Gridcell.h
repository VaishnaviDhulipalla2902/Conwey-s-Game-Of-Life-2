#ifndef Gridcell_H_
#define Gridcell_H_

class Gridcell{
    public:
        Gridcell();
        Gridcell(int x,int y,unsigned char state) ; // constructor 
        ~Gridcell() ; // destructor 
        Gridcell(const Gridcell&) ; // copy constructor 

        //getters
        int getX() {
             return x ; 
        }
        int getY() {
             return y ;
        }
        unsigned char getState() { 
            return state ;
        }
        unsigned char* getNeighbourhood() { 
            return neighbourhood;
        }
        // setters

        void setX(int x);
        void setY(int y);
        void setState(unsigned char state) ;
        void setNeighbourhood(unsigned char* neighbourhood);

        //public functions
        int count_live_neighbours(){
            int count = 0;
            for(int i=0;i<8;i++){
                if(neighbourhood[i]-'1'==0) count++;
            }
            return count;
        };
    private:
        int x,y;
        unsigned char state;
        unsigned char neighbourhood[8];

};

#endif