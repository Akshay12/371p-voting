#!/usr/bin/env python
"""
To run genTest, provide an output file to be written to as such
python genTest.py > genTest.out
"""
import sys
import random
#creat writer
w = sys.stdout


def makeBallot(n):
	s = ""
	count = 1
	while(count <=n):
		s+= str(count);
		count +=1
	s = shuffle(s)
	return s;

#shuffle values around for a random ballot
def shuffle(s):
	ballot = ""
	word = list(s)
	temp = word[:]

	for i in range(len(word)):
		randomnum = random.randint(0,len(temp)-1)
		ballot += (str(temp[randomnum])+ " ")
		temp.remove(temp[randomnum])

	return ballot


######################
names = [];
names.append("Jake");
names.append("Mark");
names.append("Elise");
names.append("Harry");
names.append("Ron");
names.append("Mary");
names.append("Lisa");
names.append("Mario");
names.append("Bowser");

#pick number of entrants. Between 2 and 10
random.seed()
count = random.randint(2,9)
finalNames = []
pos = 0
while(pos < count):
	finalNames.append(names[pos])
	pos+=1

#generate ballots
ballots = []
c2 = count
while(c2 > 0):
	ballots.append(makeBallot(count))
	c2 -=1

#make a sample input
w.write('1\n')
w.write('\n')
w.write(str(count)+'\n')
for l in finalNames:
	w.write(l+'\n')

for b in ballots:
	w.write(b+'\n')

