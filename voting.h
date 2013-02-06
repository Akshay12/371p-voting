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

// ------------
// Voting_read
// ------------

bool voting_read (std::istream&, string[]);

// ------------
// voting_write
// ------------

void voting_print (std::ostream&, string[]);

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
