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
#include <vector>

#include <string.h>
#include "Voting.h"

// ------------
// voting_read
// ------------

bool voting_read (std::istream& r, std::ostream& w, std::vector<std::string>& list) {
	using namespace std;	
	string line;
	while(r){
		getline(r,line);
		list.push_back(line);
	}
	return true;
}

// -------------
// voting_write
// -------------
	
void voting_write (std::ostream& w, std::vector<std::string>& list) {
	for(size_t i=0; i < list.size(); i++){
   		w << list[i] << std::endl;
	}
}

// -------------
// voting_solve
// -------------

void voting_solve (std::istream& r, std::ostream& w){
	std::vector<std::string> list;
	voting_read(r, w, list);
	voting_write(w,list);
}
