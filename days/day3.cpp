#include "day3.h"
#include "output.h"

#include <fstream>
#include <string>
#include <array>
#include <assert.h>

namespace aoc
{
	void Day3::run()
	{
		std::ifstream file("inputs/day3.txt", std::ios_base::in);
		std::string line;

		duplicate_priority_total_ = 0;
		group_badge_total_ = 0;

		auto group_counts = std::array<int, 26 * 2>();
		group_counts.fill(0);
		int group_index = 0;

		auto char_counts_in_left = std::array<int, 26 * 2>();
		auto char_counts_in_right = std::array<int, 26 * 2>();
		auto added_for_this_bag = std::array<bool, 26 * 2>();

		while (std::getline(file, line))
		{
			assert(line.size() % 2 == 0);
			const auto half_length = line.size() / 2;
			const std::string_view compartment1(line.c_str(), half_length);
			const std::string_view compartment2(line.c_str() + half_length, half_length);

			char_counts_in_left.fill(0);
			char_counts_in_right.fill(0);
			for (auto i = 0; i < half_length; ++i)
			{
				char_counts_in_left[compartment1[i] - (size_t)(compartment1[i] >= 'a' ? 'a' : 'A' - 26)] += 1;
				char_counts_in_right[compartment2[i] - (size_t)(compartment2[i] >= 'a' ? 'a' : 'A' - 26)] += 1;
			}

			added_for_this_bag.fill(false);
			for (auto char_index = 0; char_index < char_counts_in_left.size(); ++char_index)
			{
				if (char_counts_in_left[char_index] > 0 && char_counts_in_right[char_index] > 0)
				{
					log_.push_back(std::format("{} {} -> duplicated {}", compartment1, compartment2, char_index + (char_index >= 26 ? 'A' - 26 : 'a')));
					duplicate_priority_total_ += char_index + 1;
				}

				if (!added_for_this_bag[char_index] && (char_counts_in_left[char_index] + char_counts_in_right[char_index] > 0))
				{
					++group_counts[char_index];
					added_for_this_bag[char_index] = true;
				}
			}

			++group_index;
			if (group_index >= 3)
			{
				const auto r = std::find_if(group_counts.begin(), group_counts.end(), [](int c) -> bool { return c == 3; });
				group_badge_total_ += static_cast<int>(std::distance(group_counts.begin(), r)) + 1;

				group_counts.fill(0);
				group_index = 0;
			}
		}
		file.close();
	}

	void Day3::draw()
	{
		ImGui_print_log("Bag splits##Day3Log", log_);
		ImGui_output_field("Total of duplicate priorities", std::format("{}", duplicate_priority_total_).c_str());
		ImGui_output_field("Total of group badges", std::format("{}", group_badge_total_).c_str());
	}
}