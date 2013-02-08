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

bool voting_read (std::istream& r, std::ostream& w, std::vector<std::string>& names, std::vector<std::string>& ballots, int numCand){
	using namespace std;	
	string line;
	while(r){
		getline(r,line);
		if(!line.empty()){
		    //decide weather to push line to list of names of ballots
		    if(numCand > 0){
		        names.push_back(line);
		        numCand--;
		    }
		    else{
		        ballots.push_back(line);
		    }
		}
		else return false;
	}
	return true;
}

// -------------
// voting_write
// -------------
	
void voting_write (std::ostream& w, std::vector<std::string>& names, std::vector<std::string>& ballots) {
//for now, just print out all the lines.
	for(size_t i=0; i < names.size(); i++){
   		w << names[i] << std::endl;
	}
	
	for(size_t j=0; j< ballots.size(); j++){
	    w << ballots[j] << std::endl;
	}
}

// -------------
// voting_solve
// -------------

void voting_solve (std::istream& r, std::ostream& w){
    using namespace std;
	vector<string> names;
	vector<string> ballots;
	
	
	//get number of tests and clear the line
	int tests;
	r >> tests;
	string line;
	getline(r,line);
	
	int candidates;
	
	//this loops through all the different elections to solve
	while(tests > 0){
	    getline(r,line);
	    //find number of candidates
	    r >> candidates;
	    getline(r,line);
	    voting_read(r, w, names, ballots, candidates);
	    voting_write(w, names, ballots);
	    tests--;
	 }
}




