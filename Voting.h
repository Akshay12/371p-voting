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
