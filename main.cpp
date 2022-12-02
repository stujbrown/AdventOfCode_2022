#include "day_entry.h"

#include "days/day1.h"
#include "days/day2.h"

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
	day_functions.push_back(DayEntry("PLACEHOLDER", aoc::Day1::create));
	day_functions.push_back(DayEntry("PLACEHOLDER", aoc::Day1::create));
}

int main(int argc, char* argv[])
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
		auto& day = day_functions[day_to_run - 1];
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