#include "day10.h"
#include "output.h"

#include <fstream>
#include <string>

namespace aoc
{
	void Day10::run()
	{
		int cycle = 0;
		int reg_x = 1;
		signal_sum_ = 0;
		pixel_display_.fill(false);

		auto add_cycles = [this, &cycle](int cycles, int reg_x)
		{
			for (int i = 0; i < cycles; ++i)
			{
				++cycle;
				if ((cycle - 20) % 40 == 0)
				{
					signal_sum_ += cycle * reg_x;
					log_.push_back(std::format("--SAMPLE cycle:{}, X:{}, Sum:{}", cycle, reg_x, signal_sum_));
				}

				if (std::abs(((cycle - 1) % screen_width) - reg_x) < 2)
				{
					pixel_display_[cycle - 1] = true;
				}
			}
		};

		std::ifstream file("inputs/day10.txt", std::ios_base::in);
		std::string line;
		while (std::getline(file, line))
		{
			log_.push_back(std::format("cycle: {}, X:{}", cycle, reg_x));
			if (strncmp(line.c_str(), "addx", 4) == 0)
			{
				add_cycles(2, reg_x);
				reg_x += atoi(&line[5]);
			}
			else
				add_cycles(1, reg_x);
		}
		file.close();
	}

	void Day10::draw()
	{
		ImGui_print_log("##Day10Log", log_);

		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		const int pixel_size = 10;
		const ImVec2 start_pos = ImGui::GetCursorScreenPos();
		ImVec2 p = start_pos;

		for (int y = 0; y < screen_height; ++y)
		{
			for (int x = 0; x < screen_width; ++x)
			{
				const bool is_on = pixel_display_[screen_width * y + x];
				draw_list->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + pixel_size, p.y + pixel_size), ImU32(is_on ? ImColor(1.0f, 0.0f, 0.f, 1.0f) : ImColor(1.f, 1.f, 1.f, 1.f)));
				p.x += pixel_size;
			}
			p.y += pixel_size;
			p.x = start_pos.x;
		}
		ImGui::Dummy(ImVec2(pixel_size * screen_width, pixel_size * screen_height));

		ImGui_output_field("Signal strength sum", std::format("{}", signal_sum_).c_str());
	}
}