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

//vector contains
bool v_contains(std::vector<int>& losers, int num){
	assert(num <21);
    for(size_t i = 0; i<losers.size(); i++){
        if(losers[i] == num){
            return true;
        }
    }
    return false;
}

//----
// find vote
//----
int findVote(std::string ballot){
    using namespace std;
    char vote;
    int temp;
    int temp2;
    vote = ballot.at(0);
	temp = vote - '0';
	if(ballot.length() >1){
	    if(isdigit(ballot.at(1))){
            vote = ballot.at(1);
            temp2 = vote- '0';
            temp = (temp * 10)+temp2;
        }
    }
	assert(temp >0);
    return temp;
}
//--------
//minmax
//-------

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
	assert(max >0);
}
// -------------
// voting_write
// -------------
	
void voting_write (std::ostream& w, std::vector<std::string>& winners) {
    using namespace std;
	for(size_t h= 0; h< winners.size(); h++){
	    w<<winners[h]<<endl;
	}
}
//-------
//read
//--------

bool voting_read (std::istream& r, std::ostream& w, std::vector<std::string>& names, std::vector< std::vector<std::string> >& ballots, int numCand){
//first clear out previous candidates and ballots
    if(!(names.empty())){
        names.clear();
    }
    if(!(ballots.empty())){
        ballots.clear();
    }
//**************
	assert(ballots.empty());
	assert(names.empty());   
    using namespace std;
    vector<string> temp; 
    ballots.push_back(temp);
	int vote;	
	string line;
	while(r){
		getline(r,line);
		if(!line.empty()){
		    //decide weather to push line to list of names of ballots
		    if(numCand > 0){
				//create one vector for ballots per candidates
		        ballots.push_back(temp);
		        names.push_back(line);
		        numCand--;
		    }
		    else{
		        vote = findVote(line);
		        ballots[vote].push_back(line);
		    }
		}
		else return false;
	}
	return true;
}

//----------
//reallocate
//-----------


//takes candidates to be dropped, reallocates their votes to their next best choice
void reallocate(std::vector< std::vector<std::string> >& ballots, std::vector<int>& losers, int votes[]){
    using namespace std;
	int temp;
	vector<string> v;
	string ballot;
	int loser;
	int check;
	
	for(size_t i=0; i < losers.size(); i++){
	    loser = losers[i];
	    //v is now the vector of a loser
	    v = ballots[loser];
		for(size_t j = 0; j < v.size(); j++){
		    ballot = v[j];
		    check = findVote(ballot);
		    temp = 0;
		//continue looping until a vote is found for a possible winner
		    while(ballots[temp].empty() || (v_contains(losers,temp))){
			//check for double digits
		        if(check >9){
		            ballot = ballot.substr(3, ballot.size());
		        }
		        else{
			        ballot = ballot.substr(2, ballot.size());
			    }
			
			    //find new vote, push ballot onto that vector
			    temp = findVote(ballot);
			    check = temp;
            }
			ballots[temp].push_back(ballot);
		}
		ballots[loser].clear();
	}
}

//---------
// voting_count
//---------
//counts up the ballots and chooses a winner. Uses multiple pass throughs when necessary.
void voting_count(std::ostream& w, std::vector<std::string>& names, std::vector< std::vector<std::string> >& ballots, std::vector<std::string>& winners, std::vector<int>& losers){
    winners.clear();
    int tballots = 0;
    int votes[21]= {0};
    
    int temp;
    using namespace std;
    vector<string> v;
    
    //count votes into array
    for(size_t i = 0; i < ballots.size(); i++){
        v = ballots[i];
		votes[i] = v.size();
		tballots+= v.size();
    }
    
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
	while(max <= (tballots/2) && max != min){
		winners.clear();
	    for(int j= 0; j < 21; j++){
        	temp = votes[j];
        	if(temp == min){
        	    losers.push_back(j);
        	}
        	 
    	}
	//reallocate all ballots for losers, recount votes, recalculate max and min
		reallocate(ballots, losers, votes);

    	for(size_t h = 0; h <ballots.size(); h++){
    	    v = ballots[h];
    	    for(size_t z= 0; z < v.size();z++){
    	    }
    	}
    	
    	fill_n(votes,21,0);
    	tballots = 0;
    	//count votes again
    	for(size_t i = 0; i < ballots.size(); i++){
            v = ballots[i];
			votes[i] = v.size();
			tballots+= v.size();
        }
   
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
	}
}


// -------------
// voting_solve
// -------------

void voting_solve (std::istream& r, std::ostream& w){
    using namespace std;
	vector<string> names;
	vector< vector<string> > ballots;
	vector<string> winners;
	vector<int> losers;
	
	
	//get number of tests and clear the line
	int tests;
	r >> tests;
	assert(tests >0);
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
