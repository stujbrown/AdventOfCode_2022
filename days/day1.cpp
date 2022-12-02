#include "day1.h"
#include "output.h"

#include <fstream>
#include <string>
#include <vector>

namespace aoc
{
	void Day1::run()
	{
		std::ifstream file("inputs/day1.txt");
		std::string line;
		std::vector<int> totals;

		totals.push_back(0);
		while (std::getline(file, line))
		{
			log_.push_back(line);
			const int val = atoi(line.c_str());
			totals.back() += val;
			if (val == 0)
			{
				totals.push_back(0);
			}
		}
		file.close();

		std::sort(totals.begin(), totals.end(), std::greater<int>());
		highest_total_ = totals[0];
		highest_total_top_3_ = totals[0] + totals[1] + totals[2];
	}

	void Day1::draw() 
	{
		ImGui_print_log("Inputs##Day1Log", log_);
		ImGui_output_field("Highest calorie total", std::format("{}", highest_total_).c_str());
		ImGui_output_field("Highest calorie total of top 3", std::format("{}", highest_total_top_3_).c_str());
	}
}