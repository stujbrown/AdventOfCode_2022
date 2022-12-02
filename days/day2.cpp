#include "day2.h"
#include "output.h"

#include <fstream>
#include <sstream>

namespace aoc
{
	void Day2::run()
	{
		std::ifstream file("inputs/day2.txt");
		std::string line;

		total_score_response_as_types_ = 0;
		total_score_response_as_results_ = 0;

		while (std::getline(file, line))
		{
			char opponent = '0', response = '0';
			std::stringstream ss(line);
			ss >> opponent >> response;

			const int opponent_index = opponent - 'A';
			const int response_index = response - 'X';
			{
				const int result_score = (((opponent_index * 2) + response_index + 1) % 3) * 3;
				total_score_response_as_types_ += (response_index + 1) + result_score;
			}
			{
				const int response_score = ((opponent_index + response_index + 2) % 3) + 1;
				total_score_response_as_results_ += response_score + (response_index * 3);
			}
		}
		file.close();
	}

	void Day2::draw()
	{
		ImGui_output_field("Score for treating responses as a move type", std::format("{}", total_score_response_as_types_).c_str());
		ImGui_output_field("Score for treating responses as game outcomes", std::format("{}", total_score_response_as_results_).c_str());
	}
}