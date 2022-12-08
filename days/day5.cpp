#include "day5.h"
#include "output.h"

#include <fstream>
#include <string>
#include <vector>
#include <array>

namespace aoc
{
	void Day5::run_for_crane(bool is_crane2, std::vector<char>& out_top_items)
	{
		out_top_items.clear();

		std::ifstream file("inputs/day5.txt", std::ios_base::in);
		std::string line;

		std::vector<std::vector<char>> stacks;
		bool parsing_stacks = true;

		while (std::getline(file, line))
		{
			if (parsing_stacks)
			{
				if (line[1] == '1')
				{
					parsing_stacks = false;
					continue;
				}

				for (int column_index = 0; column_index < (line.size() + 1) / 4; ++column_index)
				{
					const char column_value = line[(column_index * 4) + 1];
					if (column_value != ' ')
					{
						stacks.resize(std::max(stacks.size(), size_t(column_index + 1)));
						stacks[column_index].insert(stacks[column_index].begin(), column_value);
					}
				}
			}
			else if (line[0] == 'm')
			{
				char* next_token = nullptr;
				const int num_to_move = atoi(strtok_s(line.data() + 5, " ", &next_token));
				(void)strtok_s(nullptr, "m", &next_token);
				const int from_column = atoi(strtok_s(nullptr, " ", &next_token));
				(void)strtok_s(nullptr, "o", &next_token);
				const int to_column = atoi(strtok_s(nullptr, " ", &next_token));

				if (is_crane2)
				{
					auto& from = stacks[from_column - 1];
					auto& to = stacks[to_column - 1];
					to.resize(to.size() + num_to_move);
					memcpy(&to[to.size() - num_to_move], &from[from.size() - num_to_move], num_to_move);
					from.resize(from.size() - num_to_move);
				}
				else
				{
					if (debug_stack_values_.size() == 0)
						record_debug_stacks(stacks, highest_value_, debug_stack_values_);

					for (int i = 0; i < num_to_move; ++i)
					{
						stacks[to_column - 1].push_back(stacks[from_column - 1].back());
						stacks[from_column - 1].pop_back();
					}

					record_debug_stacks(stacks, highest_value_, debug_stack_values_);
				}
			}
		}

		for (const auto& stack : stacks)
		{
			if (!stack.empty())
			{
				out_top_items.push_back(stack.back());
			}
		}

		file.close();
	}

	void Day5::run()
	{
		highest_value_ = 0;
		debug_stack_values_.clear();

		run_for_crane(false, crane1_top_items_);
		run_for_crane(true, crane2_top_items_);
	}

	void Day5::draw()
	{
		auto buffer = std::array<char, 64>();
		ImGui::BeginChild("##Day5Region", { 0, 230 }, false, ImGuiWindowFlags_HorizontalScrollbar);
		{
			for (int i = 0; i < debug_stack_values_.size(); ++i)
			{
				*std::format_to(buffer.data(), "##day5Crane-{}", i + 1) = '\0';
				ImGui::PlotHistogram(buffer.data(), debug_stack_values_[i].data(), (int)debug_stack_values_[i].size(), 0, nullptr, 0.f, (float)highest_value_, ImVec2(100, 200));
				ImGui::SameLine();
			}
		}
		ImGui::EndChild();

		ImGui_output_field("Top crates (crane 1)", std::string(crane1_top_items_.data(), crane1_top_items_.size()).c_str());
		ImGui_output_field("Top crates (crane 2)", std::string(crane2_top_items_.data(), crane2_top_items_.size()).c_str());
	}


	void Day5::record_debug_stacks(const std::vector<std::vector<char>>& stacks, size_t& height_counter, std::vector<std::vector<float>>& output)
	{
		output.push_back(std::vector<float>());
		std::for_each(stacks.begin(), stacks.end(), [&height_counter, &output](const std::vector<char>& s)
			{
				height_counter = std::max(height_counter, s.size());
				output.back().push_back(static_cast<float>(s.size()));
			});
	}
}