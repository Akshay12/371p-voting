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

//----
//V_contains
//----
bool v_contains(std::vector<int>&, int);

//----
// findVote
//----
int findVote(std::string);

//----
// minMax
//----
void minMax(int&, int&, int[]);

//----
// reallocate
//----
void reallocate(std::vector< std::vector<std::string> >&, std::vector<int>&, int[]);

//----
// voting_count
//----
void voting_count(std::ostream&, std::vector<std::string>&, std::vector< std::vector<std::string> >&, std::vector<std::string>&, std::vector<int>&);
// ------------
// Voting_read
// ------------

bool voting_read (std::istream&, std::ostream&, std::vector<std::string>&, std::vector< std::vector<std::string> >&, int);

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
