#pragma once
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

using Clock = std::chrono::system_clock;
using TimePoint = Clock::time_point;

void printTime(std::time_t time)
{
	auto* tm = std::gmtime(&time);
	std::cout << std::put_time(tm, "%H:%M");
}

void printDateAndTime(std::time_t time)
{
	auto* tm = std::gmtime(&time);
	std::cout << std::put_time(tm, "%Y-%m-%dT%H:%M:%S");
}