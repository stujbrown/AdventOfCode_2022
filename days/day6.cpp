#include "day6.h"
#include "output.h"

#include <fstream>
#include <string>

namespace aoc
{
	int scan(const std::string& str, int marker_len)
	{
		int sequence_start = 0;
		for (int end_index = 1; end_index < str.size(); ++end_index)
		{
			const int range_length = end_index - sequence_start;
			if (range_length == marker_len)
				return sequence_start;

			for (int scan_index = sequence_start; scan_index < end_index; ++scan_index)
			{
				if (str[scan_index] == str[end_index])
				{
					sequence_start = scan_index + 1;
				}
			}
		}

		return -1;
	}

	void Day6::run()
	{
		std::ifstream file("inputs/day6.txt", std::ios_base::in);
		std::string line;
		std::getline(file, line);
		file.close();

		log_.push_back(line);

		packet_marker_end_index_ = scan(line, 4) + 4;
		message_marker_end_index_ = scan(line, 14) + 14;

		log_.push_back(std::format("packet marker sequence = {}", std::string(&line[packet_marker_end_index_ - 4], 4).c_str()));
		log_.push_back(std::format("message marker sequence = {}", std::string(&line[message_marker_end_index_ - 14], 14).c_str()));
	}

	void Day6::draw()
	{
		ImGui_print_log("Datastream##Day6Log", log_);
		ImGui_output_field("Packet marker end index", std::format("{}", packet_marker_end_index_).c_str());
		ImGui_output_field("Message marker end index", std::format("{}", message_marker_end_index_).c_str());
	}
}