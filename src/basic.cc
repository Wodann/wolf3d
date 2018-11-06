#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <utility>

#include "util/interval_helpers.h"
#include "util/interval_tree.h"
#include "util/time_helpers.h"

namespace filesys = std::experimental::filesystem;

namespace
{
	std::time_t parseTime(const std::string& timeString)
	{
		const auto idx = timeString.find(":");
		const auto hours = std::stoi(timeString.substr(0, idx));
		const auto minutes = std::stoi(timeString.substr(idx + 1, timeString.size() - idx));

		TimePoint result;
		result += std::chrono::hours(hours) + std::chrono::minutes(minutes);

		return Clock::to_time_t(result);
	}

	std::vector<Interval<std::time_t, size_t>> parseFile(const filesys::path& filePath)
	{
		std::vector<Interval<std::time_t, size_t>> result;
		std::fstream fileStream(filePath);

		std::string line;
		size_t lineNr = 0;
		while (std::getline(fileStream, line))
		{
			const auto idx = line.find(" ");
			result.emplace_back(
				parseTime(line.substr(0, idx)),
				parseTime(line.substr(idx + 1, line.size() - idx)),
				lineNr++
			);
		}

		return result;
	}
}

int main(int argc, char *argv[])
{
	bool terminate = false;

	std::string path;
	while (!terminate)
	{
		std::cout << "Please provide a valid file path:" << std::endl;

		if (std::getline(std::cin, path))
		{
			const filesys::path filePath(path);
			std::error_code ec;
			if (filesys::exists(filePath, ec) && filesys::is_regular_file(filePath, ec))
			{
				try
				{
					auto intervals = parseFile(filePath);
					if (!intervals.empty())
					{
						// Copy vector because the original will be moved into the IntervalTree
						auto intervals2 = intervals;

						IntervalTree<std::time_t, size_t> tree(std::move(intervals));
						auto interval = findMostCommonInterval(tree, intervals2);

						std::cout << "Most cars are present between ";
						printTime(interval.first);
						std::cout << " and ";
						printTime(interval.second);
						std::cout << "." << std::endl;
					}
					else
						std::cout << "Input file is empty." << std::endl;
				}
				catch (...)
				{
					std::cout << "An error occured while parsing the input file." << std::endl;
				}
			}
			else
				std::cout << "Invalid file path : '" << path << "'" << std::endl;
		}
		else
			terminate = true;
	}
}