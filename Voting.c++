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
	w<< "" <<std::endl;
}

//calculate min and max from votes
void minMax(int& max, int& min, int votes[]){
	int temp;
    for(int j = 0; j< 21; j++){
        temp = votes[j];
        if(temp > max){
            max = temp;
        }
        if(temp < min && temp > 0){
            min = temp;
        }
    }
}


//takes candidates to be dropped, reallocates their votes to their next best choice
void reallocate(std::vector<std::string>& ballots, std::vector<int>& losers, int votes[]){
	char vote;
	int temp;
	for(size_t i=0; i < losers.size(); i++){
		for(size_t j = 0; j < ballots.size(); j++){
			vote = ballots[j].front();
			temp = vote - '0';
			while(losers[i] == temp){
				//cut off first vote, since the vote was for a loser
				ballots[j] = ballots[j].substr(2, ballots[j].size());
				//recalculate vote
				vote = ballots[j].front();
				temp = vote - '0';
				//loop continues until the vote is for someone who isn't a loser.
			}
		}
	}
}
//---------
// voting_count
//---------
//counts up the ballots and chooses a winner. Uses multiple pass throughs when necessary.
void voting_count(std::ostream& w, std::vector<std::string>& names, std::vector<std::string>& ballots, std::vector<std::string>& winners, std::vector<int>& losers){
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
	minMax(max,min,votes);

//2 conditions for being done. the max votes is >= 50% (ballots.size()/2) or the max and min ar the same, meaning all the remaining candidates are tied
	while(max <= (ballots.size()/2) && max != min){
		winners.clear();
		losers.clear();
	    for(int j= 0; j < 21; j++){
        	temp = votes[j];
        	if(temp == max){
        	    winners.push_back(names[j-1]);
        	}
        	if(temp == min){
        	    losers.push_back(j);
        	}
    	}
	//reallocate all ballots for losers, recount votes, recalculate max and min
		reallocate(ballots, losers, votes);

		fill_n(votes,21,0);
		for(size_t i = 0; i < ballots.size(); i++){
        	vote = ballots[i].front();
        	temp = vote - '0';
        	votes[temp]++;
    	}
    	max = 0;
    	min = 1000;
		minMax(max,min,votes);
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
	vector<int> losers;
	
	
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




