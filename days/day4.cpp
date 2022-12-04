#include "day4.h"
#include "output.h"

#include <fstream>
#include <string>

namespace aoc
{
	void Day4::run()
	{
		std::ifstream file("inputs/day4.txt", std::ios_base::in);
		std::string line_temp;

		contained_pair_total_ = 0;
		overlapped_pair_total_ = 0;

		while (std::getline(file, line_temp))
		{
			char* next_token = nullptr;
			const std::pair<int, int> range1 = { atoi(strtok_s(line_temp.data(), "-,", &next_token)), atoi(strtok_s(nullptr, "-,", &next_token)) };
			const std::pair<int, int> range2 = { atoi(strtok_s(nullptr, "-,", &next_token)), atoi(strtok_s(nullptr, "-,", &next_token)) };

			int overlap_type = 0;
			if (!(range1.second < range2.first || range1.first > range2.second))
			{
				++overlapped_pair_total_;
				overlap_type |= 0x1;
			}
			if (range1.first >= range2.first && range1.second <= range2.second ||
				range2.first >= range1.first && range2.second <= range1.second)
			{
				++contained_pair_total_;
				overlap_type |= 0x2;
			}

			log_.push_back(std::format("{}-{}, {}-{} : {}{}", range1.first, range1.second, range2.first, range2.second, overlap_type & 0x1 ? "overlapped " : "", overlap_type & 0x2 ? "contained" : ""));
		}

		file.close();
	}

	void Day4::draw()
	{
		ImGui_print_log("Input ranges##Day4Log", log_);
		ImGui_output_field("Entirely overlapped pair total", std::format("{}", contained_pair_total_).c_str());
		ImGui_output_field("Overlapped pair total", std::format("{}", overlapped_pair_total_).c_str());

	}
}