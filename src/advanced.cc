#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include <memory>
#include <optional>
#include <sstream>
#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include "util/interval_helpers.h"
#include "util/interval_tree.h"
#include "util/time_helpers.h"

namespace filesys = std::experimental::filesystem;

namespace
{
	std::time_t parseTime(const rapidjson::Value& object)
	{
		std::tm tm{};
		std::istringstream ss(object.GetString());
		ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");

		// std::mktime converts to local time, so calculate the inverse transformation
		auto time = std::mktime(&tm);
		auto time2 = std::mktime(std::gmtime(&time));
		const auto localTimeDiff = time2 - time;

		return time - localTimeDiff;
	}

	std::optional<std::vector<Interval<std::time_t, size_t>>> parseFile(const filesys::path& filePath)
	{
		std::vector<Interval<std::time_t, size_t>> result;

		std::fstream fileStream(filePath);
		rapidjson::IStreamWrapper wrapper(fileStream);

		rapidjson::Document doc;
		doc.ParseStream(wrapper);

		if (doc.HasParseError())
			return {};

		for (auto it = doc.Begin(); it != doc.End(); ++it)
		{
			const auto& object(*it);
			result.emplace_back(
				parseTime(object["ArrivalTime"]),
				parseTime(object["LeaveTime"]),
				object["Id"].GetUint()
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
				if (auto optIntervals = parseFile(filePath))
				{
					if (!optIntervals->empty())
					{
						// Copy vector because the original will be moved into the IntervalTree
						auto intervals2 = *optIntervals;

						IntervalTree<std::time_t, size_t> tree(std::move(*optIntervals));
						auto interval = findMostCommonInterval(tree, intervals2);

						std::cout << "Most cars are present between ";
						printDateAndTime(interval.first);
						std::cout << " and ";
						printDateAndTime(interval.second);
						std::cout << "." << std::endl;
					}
					else
						std::cout << "Input file is empty." << std::endl;
				}
				else
					std::cout << "An error occured while parsing the input file." << std::endl;
			}
			else
				std::cout << "Invalid file path : '" << path << "'" << std::endl;
		}
		else
			terminate = true;
	}
}