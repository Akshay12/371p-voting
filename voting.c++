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

#include "voting.h"

// ------------
// voting_read
// ------------

bool voting_read (std::istream& r, string[] b) {
	
	return true;
}

// -------------
// voting_write
// -------------
	
void voting_write (std::ostream& w, string[] input) {
	std::cout<<input[0]<<std::endl;
}

// -------------
// voting_solve
// -------------

void voting_solve (std::istream& r, std::ostream& w) {
	string input[]={"bob"};
	voting_write(w, input);
}
