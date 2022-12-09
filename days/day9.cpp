#include "day9.h"
#include "output.h"

#include <fstream>
#include <string>
#include <array>

namespace aoc
{
	void Day9::run()
	{
		short_tail_visits_.clear();
		long_tail_visits_.clear();

		std::array< std::pair<int, int>, 10> rope;
		rope.fill(std::pair<int, int>(0, 0));

		short_tail_visits_.insert(std::pair<int, int>(0, 0));
		long_tail_visits_.insert(std::pair<int, int>(0, 0));

		std::ifstream file("inputs/day9.txt", std::ios_base::in);
		std::string line;
		while (std::getline(file, line))
		{
			log_.push_back(line);

			char* context = nullptr;
			const char* dir = strtok_s(line.data(), " ", &context);
			const int amount = atoi(strtok_s(nullptr, " ", &context));

			for (int i = 0; i < amount; ++i)
			{
				if (dir[0] == 'R')
					rope[0].first += 1;
				else if (dir[0] == 'U')
					rope[0].second += 1;
				else if (dir[0] == 'L')
					rope[0].first -= 1;
				else if (dir[0] == 'D')
					rope[0].second -= 1;

				for (int tail_index = 1; tail_index < rope.size(); ++tail_index)
				{
					const std::pair<int, int> diff = { rope[tail_index - 1].first - rope[tail_index].first, rope[tail_index - 1].second - rope[tail_index].second };
					if (diff.second == 0 && std::abs(diff.first) > 1)
					{
						rope[tail_index].first += diff.first > 0 ? 1 : -1;
					}
					else if (diff.first == 0 && std::abs(diff.second) > 1)
					{
						rope[tail_index].second += diff.second > 0 ? 1 : -1;
					}
					else if (std::abs(diff.first) > 1 || std::abs(diff.second) > 1)
					{
						rope[tail_index].first += diff.first > 0 ? 1 : -1;
						rope[tail_index].second += diff.second > 0 ? 1 : -1;
					}

					if (tail_index == 1)
						short_tail_visits_.insert(rope[tail_index]);
					else if (tail_index == 9)
						long_tail_visits_.insert(rope[tail_index]);
				}
				log_.push_back(std::format("Head: {},{} - Tail (short): {},{}", rope[0].first, rope[0].second, rope[1].first, rope[1].second));
			}
			log_.push_back("\n");
		}
		file.close();
	}

	void Day9::draw()
	{
		ImGui_print_log("##Day9Log", log_);
		ImGui_output_field("Num visited tail spots (short)", std::format("{}", short_tail_visits_.size()).c_str());
		ImGui_output_field("Num visited tail spots (long)", std::format("{}", long_tail_visits_.size()).c_str());
	}
}