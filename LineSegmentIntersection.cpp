// LineSegmentIntersection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>

typedef std::vector<std::pair<int, int>> vector_tuples;

void intersection(vector_tuples input)
{
	vector_tuples result_segments;
	vector_tuples::const_iterator it = input.begin();
	// For a single input, the resulting line overlap projection is the input itself
	if (it != input.end())
	{
		result_segments.push_back(*it);
		++it;
	}

	// Compare the remaining inputs with candidate overlap projections denoted as result_segments.
	while (it != input.end())
	{
		bool addNewResult = false;
		for (auto it_result = result_segments.begin(); it_result != result_segments.end(); ++it_result)
		{
			std::pair<int, int> segment = *it_result;
			int rightInclusive = segment.second - (*it).first;
			int leftInclusive = (*it).second - segment.first;
			// Modify result_segments if intersection was detected
			if (rightInclusive * leftInclusive >= 0)
			{
				if ((*it).first < segment.first)
				{
					segment.first = (*it).first;
				}
				if ((*it).second > segment.second)
				{
					segment.second = (*it).second;
				}
				*it_result = segment;
				addNewResult = false;
			}
			// If no intersection, then this segment could be added to the candidate overlap projection collection
			else
			{
				addNewResult = true;
			}
		}
		if (addNewResult)
		{
			result_segments.push_back(*it);
		}
		++it;
	}

	for (auto it2 = result_segments.begin(); it2 != result_segments.end(); ++it2)
	{
		std::cout << "Segment Projections: " << (it2->first) << ", " << it2->second << std::endl;
	}
}

typedef std::pair<int, int> pair_ints;

int _tmain(int argc, _TCHAR* argv[])
{
	vector_tuples input;

	input.push_back(pair_ints(-1, 1));
	input.push_back(pair_ints(0, 2));
	input.push_back(pair_ints(-1, 0));
	input.push_back(pair_ints(3, 5));
	input.push_back(pair_ints(3, 7));
	input.push_back(pair_ints(6, 8));
	input.push_back(pair_ints(10, 18));
	//input.push_back(pair_ints(5, 11));
	intersection(input);
	return 0;
}
