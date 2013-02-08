// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <string>
#include <vector>

#include "Voting.h"

// ------------
// voting_read
// ------------

bool voting_read (std::istream& r, std::ostream& w) {
	std::vector<char*> list;
	char line[25];
	while(r){
		r.getline(line,25);
		list.push_back(line);
		w << line << std::endl;
	}
	for(size_t i=0; i < list.size(); i++){
   		w << list[i] << std::endl;
	}
	return true;
}

// -------------
// voting_write
// -------------
	
void voting_write (std::ostream& w) {
	//std::cout<<input[0]<<std::endl;
}

// -------------
// voting_solve
// -------------

void voting_solve (std::istream& r, std::ostream& w){ 
	voting_read(r, w);
}
