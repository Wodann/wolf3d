#pragma once

#include <ctime>
#include <utility>

#include "interval_tree.h"

std::pair<std::time_t, std::time_t> findMostCommonInterval(const IntervalTree<std::time_t, size_t>& tree, const std::vector<Interval<std::time_t, size_t>>& intervals)
{
	std::pair<std::time_t, std::time_t> largestInterval;
	size_t largestSize = std::numeric_limits<size_t>::lowest();
	for (const auto& start : intervals)
	{
		for (const auto& end : intervals)
		{
			if (end.stop < start.start)
				continue;

			auto contained = tree.findIntersected(start.start, end.stop);
			if (contained.size() > largestSize)
			{
				largestSize = contained.size();
				largestInterval.first = start.start;
				largestInterval.second = end.stop;
			}
		}
	}

	return largestInterval;
}