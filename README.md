# FindTargetFrom2Arrays
You are give with 2 integar array and a target. You need to come up with the pairs of values that will match with the target..


arr1 = [1, 4, 6, 8]
arr2 = [3,5, 7, 2]

target = 12..

expected output is (8,3) (6,5) (4, 7) (6,7) (8,5).

Two versions are implemented, Version2 is optimal.


Logic Version 2 :-
Sort the arrays
then compare the addition of last element of 1st array and first element of 2nd array
	
	arr1 >      1    4    6    8 |
			

	arr2 v  2   X   X     X    10 (2+8) less than target 12, so remaining all item of first row would be lesser 
	
		3   X   X     X    11 (3+8)

	        5   X   X     11(5,6) 13 (5,7) (13 is greater than taret, so will will not consider the (7, 8)

		7   X   11(7,4) 13(7,6) X

So finally we can add all the pairs in an array to be returned as the answer.
which is (3,8), (5,6), (7,4), (5,7), (7,6). We can add 2,8 as well but not required.

Implementation.

	The above calculations are stored in multimap( as it allows duplicates), with key as modulo difference
	of target and the sum of pair shown above, and value as a Pair of those values.

	forex:- multimap[2] = {2, 8};
		multimap[1] = {3,11};
		multimap[1] = {5,7}; // Modulo difference..



