#include "SuperGrid.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
	int NR,NC,R,C,k,s;
	NR = stoi(argv[1]);
	NC = stoi(argv[2]); 
	R = stoi(argv[3]);
	C = stoi(argv[4]);
	k = stoi(argv[5]);
	s = stoi(argv[6]);
	SuperGrid supergrid(NR,NC,R,C,k,s);
	supergrid.generate_initial_state();
	cout << supergrid;
	supergrid.synchronizeSuperGrid();
	cout << supergrid;
	return 0;
}