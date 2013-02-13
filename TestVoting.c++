                                                                     
                                                                     
                                                                     
                                             
// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -lcppunit -ldl -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz.c++.app
    % valgrind TestCollatz.c++.app >& TestCollatz.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"
 
    // ----
    // read
    // ----


void test_read_1() {
        std::istringstream r("2\n ben\njohn\n1 2\n1 2\n 2 1");
        std::vector<std::string> names;
        std::vector<std::vector<string> > ballots;

        const bool b = voting_read(r, names, ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(names.size() == 2);
        CPPUNIT_ASSERT(ballots.size() == 3);
        CPPUNIT_ASSERT(names[0] == "ben");
        CPPUNIT_ASSERT(names[1] == "john");
    }
void test_read_2() {
        std::istringstream r("2\nAkshay\nGreg\n1 2\n1 2\n 2 1");
        std::vector<std::string> names;
        std::vector<std::vector<string> > ballots;
        const bool b = voting_read(r, names, ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(names.size() == 2);
        CPPUNIT_ASSERT(ballots.size() == 3);
        CPPUNIT_ASSERT(names[0] == "Akshay");
        CPPUNIT_ASSERT(names[1] == "Greg");
    }

void test_read_3() {
        std::istringstream r("2\n John Doe\nJane Smith\nSirhan Sirhan\n"\n1 2\n1 2\n 2 1");
        std::vector<std::string> names;
        std::vector<std::vector<string> > ballots;

        const bool b = voting_read(r, names, ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(names.size() == 2);
        CPPUNIT_ASSERT(ballots.size() == 3);
        CPPUNIT_ASSERT(names[0] == "John Doe");
        CPPUNIT_ASSERT(names[1] == "Jane Smith");
	   CPPUNIT_ASSERT(names[1] == "Sirhan Sirhan");
    }


void test_read_4() {
        std::istringstream r("5\nAll\nBees\nCry\nDeep\nEndlessy\n1 2 3 4 5\n1 2 3 4 5\n 5 4 3 2 1");
        std::vector<std::string> names;
        std::vector<std::vector<string> > ballots;

        const bool b = voting_read(r, names, ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(names.size() == 5);
        CPPUNIT_ASSERT(ballots.size() == 3);
        CPPUNIT_ASSERT(names[0] == "All");
        CPPUNIT_ASSERT(names[1] == "Bees");
        CPPUNIT_ASSERT(names[2] == "Cry");
        CPPUNIT_ASSERT(names[3] == "Deep");
        CPPUNIT_ASSERT(names[4] == "Endlessy");

    }

    // -----
    // print
    // -----

    void test_print1 () {
        std::ostringstream w;
	vector<string> v = {"Akshay Vyas"};
        voting_write(w, v);
        CPPUNIT_ASSERT(w.str() == "Akshay Vyas\n");}


    void test_print2 () {
        std::ostringstream w;
	vector<string> v = {"Greg Wadley", "Akshay Vyas"};
        voting_write(w, v);
        CPPUNIT_ASSERT(w.str() == "greg Wadley\nAkshay Vyas\n");}


    void test_print3 () {
        std::ostringstream w;
	vector<string> v = {"Glenn Downing", "Glenn Downing"};
        voting_write(w, v);
        CPPUNIT_ASSERT(w.str() == "Glenn Downing\nGlenn Downing\n");}
 void test_print4 () {
        std::ostringstream w;
	vector<string> v = {"Pikachu"};
        voting_write(w, v);
        CPPUNIT_ASSERT(w.str() == "Pikachu\n");}

 void test_print5 () {
        std::ostringstream w;
	vector<string> v = {"Cho-Gath"};
        voting_write(w, v);
        CPPUNIT_ASSERT(w.str() == "Cho-Gath\n");}

 void test_print6 () {
        std::ostringstream w;
	vector<string> v = {"Taric", "Lee Sin", "Riven"};
        voting_write(w, v);
        CPPUNIT_ASSERT(w.str() == "Taric","lee Sin". "Riven");}

    // -----
    // solve
    // -----

  void test_solve_1 () {
        std::istringstream r("1\n\n2\nJohn\nJane\n1 2\n\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John\nJane");
    }
    
    void test_solve_2 () {
        std::istringstream r("1\n\n2\nJohnny\nTaylor nelson\n1 2\n2 1\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Johnny\nTaylor nelson\n");
    }
    
    void test_solve_3 () {
        std::istringstream r("1\n\n3\nAkshay\nGreg\nDowning\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Akshay\n");
    }
//--------
//reallocate
//---------

	void test_reallocate_1() {
	 std::vector<std::vector<string> > ballots;
	 std::vector<int>& losers
	 int votes[]
	}

//--------
//count
//--------

	void test_count_1() {
	std::ostringstream w;
	vector<string> v = {"Taric", "Lee Sin", "Riven"};
	std::vector<std::vector<string> > ballots;
	vector<string> winner = {"Taric"};
	vector<int> losers = {2,3};
	voting_count(w, v, ballots, winners, losers)
	
	}

