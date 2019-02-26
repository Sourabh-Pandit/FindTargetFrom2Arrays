// AmazonAirplaneProblem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <set>
#include<vector>
#include<algorithm>
#include <iterator>
#include <map>
/*
you are give with 2 integar array and a target.

you need to come up with the pairs of values that will match with the target..

arr1 = [1, 4, 6, 8]
arr2 = [3,5, 7, 2]

target = 12..

expected output is (8,3) (6,5) (4, 7) (6,7) (8,5).



Assumptions :- Non repeat elements 

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

*/
using namespace std;

vector<pair<int, int>> findTargetVer2() {
	int arr1[] = { 1, 4, 6, 8 };
	int arr2[] = { 3, 5, 7, 2 };
	int target = 12;

	vector< pair<int, int> > output;

	set<int> arr1Set;
	insert_iterator< set<int> > itr(arr1Set, arr1Set.begin());
	copy(&arr1[0], &arr1[3] + 1, itr);
	set<int> arr2Set;
	insert_iterator< set<int> > itr2(arr2Set, arr2Set.begin());
	copy(&arr2[0], &arr2[3] + 1, itr2);
	
	auto rItr1 = arr1Set.rbegin();
	auto rItr2 = arr2Set.rbegin();

	int max = *rItr1 + *rItr2;

	auto fItr1 = arr1Set.begin();
	auto fItr2 = arr2Set.begin();

	int min = *fItr1 + *fItr2;

	if (target > max) {
		target = max;
	}
	if (target < min) {
		target = min;
	}

	multimap<int, pair<int, int>> temp;

	for (auto itr1 = arr1Set.crbegin(); itr1 != arr1Set.crend();) {
		auto itr2 = arr2Set.begin();
		for (; itr2 != arr2Set.end();) {

			cout << " itr1 =>" << *itr1 << " itr2 =>" << *itr2 << endl;

			if (target > (*itr1 + *itr2)) {
				temp.insert(make_pair((target - (*itr1 + *itr2)), make_pair(*itr1, *itr2)));
				itr2++;
			}
			else {
				temp.insert(make_pair(((*itr1 + *itr2) - target), make_pair(*itr1, *itr2)));
				itr1++;
			}
		}
		if (itr2 == arr2Set.end()) break;
	}
	
	for (int i = 0; i < target; i++) {
		auto itr = temp.equal_range(i);
		if (itr.first != itr.second) {
			for (auto x = itr.first; x != itr.second; x++)
				output.push_back(make_pair(x->second.first, x->second.second));
			break;
		}
		
	}
	return output;
	
}
vector<pair<int, int>> findTarget() {
	int arr1[] = { 1, 4, 6, 8 };
	int arr2[] = { 3, 5, 7, 2 };
	int target = 12;

	vector< pair<int, int> > output;

	set<int> arr1Set;
	insert_iterator< set<int> > itr(arr1Set, arr1Set.begin());
	copy(&arr1[0], &arr1[3] + 1, itr);
	set<int> arr2Set;
	insert_iterator< set<int> > itr2(arr2Set, arr2Set.begin());
	copy(&arr2[0], &arr2[3] + 1, itr2);


	auto rItr1 = arr1Set.rbegin();
	auto rItr2 = arr2Set.rbegin();

	int max = *rItr1 + *rItr2 ;

	auto fItr1 = arr1Set.begin();
	auto fItr2 = arr2Set.begin();

	int min = *fItr1 + *fItr2  ;

	if (target > max) {
		target = max;
	}
	if (target < min) {
		target = min;
	}
	int ltarget = target;

	for (int a : arr2) {
		
		int searchItem = ltarget - a;
		if (a < 0) {
			continue;
		}
		auto itr = arr1Set.find(searchItem);
		if (itr != arr1Set.end()) {
			output.push_back(make_pair(a, *itr));
		}
	}
	int lowtarget = target;
	int hightarget = target;
	bool lowDone = false, highDone = false;
	if (output.size() == 0) {
		while (true) {
		
			lowtarget--;
		if (ltarget < min) {
			lowDone = true;
		}
		hightarget++;
		if(hightarget > max) {
			highDone = true;
		}

		for (int a : arr2) {

			int searchItem = lowtarget - a;

			if (a < 0) {
				continue;
			}
			auto itr = arr1Set.find(searchItem);
			if (itr != arr1Set.end()) {
				output.push_back(make_pair(a, *itr));
			}
		}
		for (int a : arr2) {

			int searchItem = hightarget - a;

			if (a < 0) {
				continue;
			}
			auto itr = arr1Set.find(searchItem);
			if (itr != arr1Set.end()) {
				output.push_back(make_pair(a, *itr));
			}
		}
		if (output.size() != 0) {
			break;
		}
		else if (lowDone && highDone) {
				break;
			}
		
		}	
	}

	return output;
}
int main()
{
	vector<pair<int, int>> ret = findTargetVer2();

	for (auto itr = ret.begin(); itr != ret.end(); itr++)
	{
		pair<int, int> op = *itr;
		std::cout << "(" << op.first << ", " << op.second << " )"<<endl;
	}
    std::cout << "Hello World!\n"; 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
