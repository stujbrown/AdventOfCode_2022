#include <iostream>
#include <functional>
#include <format>

#include "days/aoc_days.h"

using namespace std;

void run_day(int day, std::function<void()> f)
{
	cout << format("Running day {}:\n", day);
	f();
}

void add_days(std::vector<std::function<void()>>& day_functions)
{
	day_functions.push_back(aoc::day1);
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

	std::vector<std::function<void()>> day_functions;
	add_days(day_functions);


	if (day_to_run <= 0 || day_to_run > day_functions.size())
	{
		day_to_run = -1;
	}

	if (day_to_run == -1)
	{
		for (int i = 0; i < day_functions.size(); ++i)
		{
			run_day(i + 1, day_functions[i]);
		}
	}
	else
	{
		if (day_to_run )
		{
			run_day(day_to_run, day_functions[day_to_run - 1]);
		}
	}

	return 0;
}
