#include "day14.h"
#include "output.h"

#include <fstream>
#include <string>

namespace aoc
{
	Day14::Sim simulate(bool with_floor)
	{
		Day14::Sim sim = Day14::Sim();
		std::ifstream file("inputs/day14.txt", std::ios_base::in);
		std::string line;
		while (std::getline(file, line))
		{
			const char* x_str = nullptr;
			char* context = nullptr;
			std::pair<int, int> last = std::make_pair(-1, -1);
			do
			{
				x_str = strtok_s(context == nullptr ? line.data() : nullptr, ",", &context);
				const char* y_str = strtok_s(nullptr, " ", &context);
				(void)strtok_s(nullptr, " ", &context);
				if (x_str != nullptr && y_str != nullptr)
				{
					const int x = atoi(x_str);
					const int y = atoi(y_str);
					const auto current = std::make_pair(x, y);
					sim.cave_[current] = '#';
					sim.lowest_coordinate_.first = std::min(sim.lowest_coordinate_.first, x);
					sim.lowest_coordinate_.second = std::min(sim.lowest_coordinate_.second, y);
					sim.highest_coordinate_.first = std::max(sim.highest_coordinate_.first, x);
					sim.highest_coordinate_.second = std::max(sim.highest_coordinate_.second, y);

					std::pair<int, int> diff = std::make_pair(last.first - x, last.second - y);
					while (last.first != -1 && last != current)
					{
						last.first += diff.first > 0 ? -1 : (diff.first < 0 ? 1 : 0);
						last.second += diff.second > 0 ? -1 : (diff.second < 0 ? 1 : 0);
						sim.cave_[last] = '#';
					}
					last = current;
				}
			} while (x_str != nullptr);
		}
		file.close();


		int floor_y = sim.highest_coordinate_.second + 2;

		bool falling_into_abyss = false;
		while (!falling_into_abyss)
		{
			std::pair<int, int> sand_pos = std::make_pair(500, 0);
			++sim.units_of_sand_;
			bool rested = false;
			while (!rested && (with_floor || sand_pos.second < sim.highest_coordinate_.second))
			{
				if (with_floor && sand_pos.second == floor_y - 1)
				{
					rested = true;
				}
				else if (!sim.cave_.contains(std::make_pair(sand_pos.first, sand_pos.second + 1)))
				{
					++sand_pos.second;
				}
				else if (!sim.cave_.contains(std::make_pair(sand_pos.first - 1, sand_pos.second + 1)))
				{
					--sand_pos.first;
					++sand_pos.second;
				}
				else if (!sim.cave_.contains(std::make_pair(sand_pos.first + 1, sand_pos.second + 1)))
				{
					++sand_pos.first;
					++sand_pos.second;
				}
				else
				{
					rested = true;
				}
			}
			if (rested)
			{
				sim.cave_[sand_pos] = '+';
				if (sand_pos == std::make_pair(500, 0))
				{
					break;
				}
			}
			else
				falling_into_abyss = true;

		}

		return sim;
	}

	void Day14::run()
	{
		no_floor_simulation_ = simulate(false);
		final_simulation_ = simulate(true);
	}

	void draw_sim(const Day14::Sim& sim, int pixel_size, ImVec2 start_pos)
	{
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImVec2 p = start_pos;

		for (int y = sim.lowest_coordinate_.second; y <= sim.highest_coordinate_.second; ++y)
		{
			for (int x = sim.lowest_coordinate_.first; x <= sim.highest_coordinate_.first; ++x)
			{
				const auto val_result = sim.cave_.find(std::make_pair(x, y));
				const char value = val_result != sim.cave_.end() ? (*val_result).second : '.';
				draw_list->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + pixel_size, p.y + pixel_size),
					ImU32(value == '#' ? ImColor(1.0f, 1.0f, 1.f, 1.0f) :
						(value == '+' ? ImColor(1.f, 0.8f, 0.f, 1.f) : ImColor(0.1f, 0.1f, 0.1f, 1.f))));
				p.x += pixel_size;
			}
			p.y += pixel_size;
			p.x = start_pos.x;
		}
	}

	void Day14::draw()
	{
		ImVec2 start_pos = ImGui::GetCursorScreenPos();

		const int pixel_size = 7;
		draw_sim(no_floor_simulation_, pixel_size, start_pos);
		const int width = (no_floor_simulation_.highest_coordinate_.first - no_floor_simulation_.lowest_coordinate_.first);
		start_pos.x += (width * pixel_size) + 50;
		draw_sim(final_simulation_, pixel_size, start_pos);

		ImGui::Dummy(ImVec2(pixel_size * ((final_simulation_.highest_coordinate_.first - final_simulation_.lowest_coordinate_.first) + 1),
			pixel_size * ((final_simulation_.highest_coordinate_.second - final_simulation_.lowest_coordinate_.second) + 1)));


		ImGui_output_field("Units of sand (no floor)", std::format("{}", no_floor_simulation_.units_of_sand_ - 1).c_str());
		ImGui_output_field("Units of sand (floor)", std::format("{}", final_simulation_.units_of_sand_).c_str());
	}
}