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
	
void voting_write (std::ostream& w, std::vector<std::string>& winners) {
//for now, just print out all the lines.
	for(size_t i=0; i < winners.size(); i++){
   		w << winners[i] << std::endl;
	}
}
//---------
// voting_count
//---------
//counts up the ballots and chooses a winner. Uses multiple pass throughs when necessary.
void voting_count(std::ostream& w, std::vector<std::string>& names, std::vector<std::string>& ballots, std::vector<std::string>& winners, std::vector<std::string>& losers){
    int votes[21]= {0};
    
    int temp;
    using namespace std;
    char vote;
    //count votes into array
    for(size_t i = 0; i < ballots.size(); i++){
        vote = ballots[i].front();
        temp = vote - '0';
        votes[temp]++;
    }
    //find max
    int max = 0;
    int min = 1000;
    for(int j = 0; j< 21; j++){
        temp = votes[j];
        if(temp > max){
            max = temp;
        }
        if(temp < min && temp > 0){
            min = temp;
        }
    }
    for(int j= 0; j < 21; j++){
        temp = votes[j];
        if(temp == max){
            winners.push_back(names[j-1]);
        }
        if(temp == min){
            losers.push_back(names[j-1]);
        }
    }

    
}

// -------------
// voting_solve
// -------------

void voting_solve (std::istream& r, std::ostream& w){
    using namespace std;
	vector<string> names;
	vector<string> ballots;
	vector<string> winners;
	vector<string> losers;
	
	
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
	    voting_count(w, names, ballots, winners, losers);
	    voting_write(w, winners);
	    tests--;
	
	 }
}




