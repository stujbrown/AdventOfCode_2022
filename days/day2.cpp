#include "day2.h"
#include "output.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace aoc
{
	int calc_response_as_type(char opponent, char response)
	{
		if (opponent == 'A')
		{
			if (response == 'X') return 1 + 3;
			else if (response == 'Y') return 2 + 6;
			else if (response == 'Z') return 3 + 0;
		}
		else if (opponent == 'B')
		{
			if (response == 'X') return 1 + 0;
			else if (response == 'Y') return 2 + 3;
			else if (response == 'Z') return 3 + 6;

		}
		else if (opponent == 'C')
		{
			if (response == 'X') return 1 + 6;
			else if (response == 'Y') return 2 + 0;
			else if (response == 'Z') return 3 + 3;
		}
		return 0;
	}

	int calc_response_as_result(char opponent, char response)
	{
		if (opponent == 'A')
		{
			if (response == 'X') return 3 + 0;
			else if (response == 'Y') return 1 + 3;
			else if (response == 'Z') return 2 + 6;
		}
		else if (opponent == 'B')
		{
			if (response == 'X') return 1 + 0;
			else if (response == 'Y') return 2 + 3;
			else if (response == 'Z') return 3 + 6;

		}
		else if (opponent == 'C')
		{
			if (response == 'X') return 2 + 0;
			else if (response == 'Y') return 3 + 3;
			else if (response == 'Z') return 1 + 6;
		}
		return 0;
	}

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

			total_score_response_as_types_ += calc_response_as_type(opponent, response);
			total_score_response_as_results_ += calc_response_as_result(opponent, response);
		}
		file.close();
	}

	void Day2::draw()
	{
		ImGui_output_field("Score for treating responses as a move type", std::format("{}", total_score_response_as_types_).c_str());
		ImGui_output_field("Score for treating responses as game outcomes", std::format("{}", total_score_response_as_results_).c_str());
	}
}