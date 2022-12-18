#include "day_entry.h"

#include "days/day1.h"
#include "days/day2.h"
#include "days/day3.h"
#include "days/day4.h"
#include "days/day5.h"
#include "days/day6.h"
#include "days/day7.h"
#include "days/day8.h"
#include "days/day9.h"
#include "days/day10.h"
#include "days/day11.h"
#include "days/day12.h"
#include "days/day13.h"
#include "days/day14.h"
#include "days/day15.h"

#include "window.h"

#include <vector>
#include <memory>
#include <functional>
#include <string>

using namespace std;


void add_days(vector<DayEntry>& day_functions);


void add_days(vector<DayEntry>& day_functions)
{
	day_functions.push_back(DayEntry("Day 1: Calorie Counting", aoc::Day1::create));
	day_functions.push_back(DayEntry("Day 2: Rock Paper Scissors", aoc::Day2::create));
	day_functions.push_back(DayEntry("Day 3: Rucksack Reorganization", aoc::Day3::create));
	day_functions.push_back(DayEntry("Day 4: Camp Cleanup", aoc::Day4::create));
	day_functions.push_back(DayEntry("Day 5: Supply Stacks", aoc::Day5::create));
	day_functions.push_back(DayEntry("Day 6: Tuning Trouble", aoc::Day6::create));
	day_functions.push_back(DayEntry("Day 7: No Space Left On Device", aoc::Day7::create));
	day_functions.push_back(DayEntry("Day 8: Treetop Tree House", aoc::Day8::create));
	day_functions.push_back(DayEntry("Day 9: Rope Bridge", aoc::Day9::create));
	day_functions.push_back(DayEntry("Day 10: Cathode-Ray Tube", aoc::Day10::create));
	day_functions.push_back(DayEntry("Day 11: Monkey in the Middle", aoc::Day11::create));
	day_functions.push_back(DayEntry("Day 12: Hill Climbing Algorithm", aoc::Day12::create));
	day_functions.push_back(DayEntry("Day 13: Distress Signal", aoc::Day13::create));
	day_functions.push_back(DayEntry("Day 14: Regolith Reservoir", aoc::Day14::create));
	day_functions.push_back(DayEntry("Day 15: Beacon Exclusion Zone", aoc::Day15::create));
}

int WinMain(int argc, char* argv[])
{
	int day_to_run = -1;
	if (argc > 0 && argc <= 64)
	{
		for (int i = 0; i < argc; ++i)
		{
			const std::string_view arg(argv[i]);
			if (arg.compare("-day") == 0)
			{
				if (i + 1 < argc)
				{
					day_to_run = atoi(argv[i + 1]);
				}
			}
		}
	}

	vector<DayEntry> day_functions;
	add_days(day_functions);

	if (day_to_run <= 0 || day_to_run > day_functions.size())
	{
		day_to_run = -1;
	}

	// Run specific day (without window)
	if (day_to_run != -1)
	{
		auto& day = day_functions[(size_t)day_to_run - 1];

		day.run();
	}
	else
	{
		if (window_create())
		{
			window_run(move(day_functions));
		}

		window_cleanup();
	}
}