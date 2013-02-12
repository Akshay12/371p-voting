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
//first clear out previous candidates and ballots
    if(!(names.empty())){
        names.clear();
    }
    if(!(ballots.empty())){
        ballots.clear();
    }
//**************    
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
	int temp2;
	for(size_t i=0; i < ballots.size(); i++){
	    vote = ballots[i].at(0);
		temp = vote - '0';
		if(ballots[i].length() >1){
		    if(isdigit(ballots[i].at(1))){
                vote = ballots[i].at(1);
                temp2 = vote- '0';
                temp = (temp * 10)+temp2;
            }
        }
	//check for candidates numbered 10 or greater
		for(size_t j = 0; j < losers.size(); j++){
			while(losers[j] == temp){
		        //cut off first vote, since the vote was for a loser
		        if(isdigit(ballots[i].at(1))){
		            ballots[i] = ballots[i].substr(3, ballots[i].size());
		        }
		        else{
			        ballots[i] = ballots[i].substr(2, ballots[i].size());
			    }
			    //recalculate vote
			    vote = ballots[i].at(0);
			    temp = vote - '0';
			    if(ballots[i].length() > 1){
			        if(isdigit(ballots[i].at(1))){
                        vote = ballots[i].at(1);
                        temp2 = vote- '0';
                        temp = (temp * 10)+temp2;
                    }
                }
                
			    j = 0;
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
    winners.clear();
    int votes[21]= {-1};
    
    int temp;
    using namespace std;
    char vote;
    int temp2;
    
    //count votes into array
    for(size_t i = 0; i < ballots.size(); i++){
        vote = ballots[i].at(0);
        temp = vote - '0';
        if(ballots[i].length()>1){
            if(isdigit(ballots[i].at(1))){
                vote = ballots[i].at(1);
                temp2 = vote- '0';
                temp = (temp * 10)+temp2;
            }
        }
        votes[temp]++;
    }
    //w<<""<<endl;
    //find max
    int max = 0;
    int min = 1000;
	minMax(max,min,votes);
	for(int m=0; m<21; m++){
	    temp = votes[m];
	    if(temp == max){
       	    winners.push_back(names[m-1]);
       	}
	}

//2 conditions for being done. the max votes is >= 50% (ballots.size()/2) or the max and min ar the same, meaning all the remaining candidates are tied
	while(max <= (ballots.size()/2) && max != min){
		winners.clear();
	    for(int j= 0; j < 21; j++){
        	temp = votes[j];
        	if(temp == min || temp ==0){
        	    losers.push_back(j);
        	}
    	}
    	/*
    	for(size_t h = 0; h <losers.size(); h++){
    	    w<< losers[h] << " ";
    	}
    	w<<""<<endl;
    	w<<""<<endl;
    	*/
	//reallocate all ballots for losers, recount votes, recalculate max and min
		reallocate(ballots, losers, votes);

		fill_n(votes,21,-1);
		//count all votes again
		for(size_t i = 0; i < ballots.size(); i++){
        	vote = ballots[i].at(0);
        	temp = vote - '0';
        	if(ballots[i].length() >1){
        	    if(isdigit(ballots[i].at(1))){
                    vote = ballots[i].at(1);
                    temp2 = vote- '0';
                    temp = (temp * 10)+temp2;
                }
            }
        	votes[temp]++;
    	}
    	//w<<""<<endl;
    	max = 0;
    	min = 1000;
		minMax(max,min,votes);
		//new max compute winners again
		for(int k=0; k<21; k++){
		    temp = votes[k];
		    if(temp == max){
        	    winners.push_back(names[k-1]);
        	}
		}
	    //w<<"max: " <<max <<endl;
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
	getline(r,line);
	
	//this loops through all the different elections to solve
	while(tests > 0){	    
	    //find number of candidates
	    r >> candidates;
	    getline(r,line);
	    //read names and ballots, do the calculation, print the results. finally, decrment tests and print another
	    //newline if there are more tests to be done.
	    voting_read(r, w, names, ballots, candidates);
	    voting_count(w, names, ballots, winners, losers);
	    voting_write(w, winners);
	    tests--;
	    //newline if there are more tests
	    if(tests >0){
	        w<<endl;
	    }
	    losers.clear();
	 }
}




