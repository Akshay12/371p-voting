// --------------------------
// projects/collatz/Collatz.h
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------

#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>
#include <vector>

// ------------
// Voting_read
// ------------

bool voting_read (std::istream&, std::ostream&, std::vector<std::string>&, std::vector<std::string>&);

// ------------
// voting_write
// ------------

void voting_write (std::ostream&, std::vector<std::string>&);

//-------------
// voting_count
//------------

void voting_count(std::ostream&, std::vector<std::string>&, std::vector<std::string>&, std::vector<std::string>&, std::vector<std::string>&);
// -------------
// voting_solve
// -------------

/**
 * read, eval, print loop
 * @param r a std::istream
 * @param w a std::ostream
 */
void voting_solve (std::istream&, std::ostream&);

#endif // Collatz_h
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
	for(size_t i=0; i < ballots.size(); i++){
	    vote = ballots[i].at(0);
		temp = vote - '0';
		for(size_t j = 0; j < losers.size(); j++){
			while(losers[j] == temp){
				//cut off first vote, since the vote was for a loser
				ballots[i] = ballots[i].substr(2, ballots[i].size());
				//recalculate vote
				vote = ballots[i].at(0);
				temp = vote - '0';
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
    int votes[21]= {-1};
    
    int temp;
    using namespace std;
    char vote;
    //count votes into array
    for(size_t i = 0; i < ballots.size(); i++){
        vote = ballots[i].at(0);
        temp = vote - '0';
        votes[temp]++;
        //w<< ballots[i] << endl;
    }
    //w<<""<<endl;
    //find max
    int max = 0;
    int min = 1000;
	minMax(max,min,votes);

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
        	votes[temp]++;
        	//w<<ballots[i]<<endl;
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




// -------------------------------
// projects/collatz/RunCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// -------------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall Collatz.c++ RunCollatz.c++ -o RunCollatz
    % valgrind RunCollatz < RunCollatz.in > RunCollatz.out

To configure Doxygen:
    % doxygen -g
That creates the file "Doxyfile".
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    % doxygen Doxyfile
*/

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------

#include <iostream> // cin, cout, ios_base
#include <string>

// ----
// main
// ----

int main () {
    using namespace std;
//  ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    voting_solve(cin, cout);
    return 0;}
