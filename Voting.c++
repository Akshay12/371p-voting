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

#include "Voting.h"

// ------------
// voting_read
// ------------

bool voting_read (std::istream& r, std::ostream& w) {
	char line[25];
	r >> line;
	if(!r)
		return false;
	w << line << std::endl;
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
	voting_read(w, r);
}
