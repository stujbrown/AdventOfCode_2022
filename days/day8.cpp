#include "day8.h"
#include "output.h"

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

namespace aoc
{
	void update_state(const std::vector<std::string>& grid, int x, int y, int& highest_tree, std::vector<bool>& visible_states)
	{
		if (grid[y][x] - '0' > highest_tree)
			visible_states[grid[0].size() * y + x] = true;

		highest_tree = std::max(grid[y][x] - '0', highest_tree);
	}

	void scan_row(const std::vector<std::string>& grid, int row, std::vector<bool>& visible_states)
	{
		int highest_tree = -1;
		for (int i = 0; i < (int)grid[0].size(); ++i)	update_state(grid, i, row, highest_tree, visible_states);
		highest_tree = -1;
		for (int i = (int)grid[0].size() - 1; i >= 0; --i) update_state(grid, i, row, highest_tree, visible_states);
	}

	void scan_column(const std::vector<std::string>& grid, int column, std::vector<bool>& visible_states)
	{
		int highest_tree = -1;
		for (int i = 0; i < (int)grid.size(); ++i) update_state(grid, column, i, highest_tree, visible_states);
		highest_tree = -1;
		for (int i = (int)grid.size() - 1; i >= 0; --i) update_state(grid, column, i, highest_tree, visible_states);
	}

	size_t calc_score(const std::vector<std::string>& grid, int x, int y)
	{
		size_t counter1 = 0, counter2 = 0, counter3 = 0, counter4 = 0;
		for (int current_x = x + 1; current_x < grid[0].size(); ++current_x)
		{
			++counter1;
			if (grid[y][x] <= grid[y][current_x]) break;
		}

		for (int current_x = x - 1; current_x >= 0; --current_x)
		{
			++counter2;
			if (grid[y][x] <= grid[y][current_x]) break;
		}

		for (int current_y = y + 1; current_y < grid.size(); ++current_y)
		{
			++counter3;
			if (grid[y][x] <= grid[current_y][x]) break;
		}

		for (int current_y = y - 1; current_y >= 0; --current_y)
		{
			++counter4;
			if (grid[y][x] <= grid[current_y][x]) break;
		}

		return (counter1 * counter2) * counter3 * counter4;
	}

	void Day8::run()
	{
		grid_ = std::vector<std::string>();
		total_visible_ = 0;
		highest_score_ = 0;

		std::ifstream file("inputs/day8.txt", std::ios_base::in);
		std::string line;
		while (std::getline(file, line))
			grid_.push_back(line);
		file.close();

		const auto width = grid_[0].size();
		visible_states_ = std::vector<bool>();
		visible_states_.resize(width * grid_.size(), false);

		for (int row = 0; row < grid_.size(); ++row)
			scan_row(grid_, row, visible_states_);

		for (int column = 0; column < width; ++column)
			scan_column(grid_, column, visible_states_);

		for (int y = 0; y < grid_.size(); ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				highest_score_ = std::max(calc_score(grid_, x, y), highest_score_);
				total_visible_ += visible_states_[width * y + x] ? 1 : 0;
			}
		}
	}

	void Day8::draw()
	{
		ImGui::BeginChild("##day8grid", ImVec2(800, 500), false, ImGuiWindowFlags_HorizontalScrollbar);
		for (int y = 0; y < grid_.size(); ++y)
		{
			for (int x = 0; x < grid_[0].size(); ++x)
			{
				ImGui::TextColored(visible_states_[grid_[0].size() * y + x] ? ImVec4(0, 1, 0, 1) : ImVec4(1, 1, 1, 1),
					"%c", grid_[y][x]);
				if (x != grid_[0].size() - 1)
				{
					ImGui::SameLine();
				}
			}
		}
		ImGui::EndChild();
		ImGui::Spacing();

		ImGui_output_field("Visible trees", std::format("{}", total_visible_).c_str());
		ImGui_output_field("Highest possible score", std::format("{}", highest_score_).c_str());

	}
}