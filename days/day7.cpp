#include "day7.h"
#include "output.h"

#include <fstream>
#include <vector>

namespace aoc
{
	namespace day7
	{
		struct Node
		{
			std::string dir_name;
			size_t total_size;
		};
	}

	void Day7::run()
	{
		total_size_for_under_100000_ = 0;
		total_size_for_dir_to_delete_ = 0;

		std::ifstream file("inputs/day7.txt", std::ios_base::in);
		std::string line;

		std::vector<std::unique_ptr<day7::Node>> nodes;
		std::vector<day7::Node*> stack;

		while (std::getline(file, line))
		{
			if (line[0] == '$')
			{
				if (strncmp(&line[2], "cd", 2) == 0)
				{
					if (strncmp(&line[5], "..", 2) == 0)
					{
						stack.pop_back();
					}
					else
					{
						std::string dir(&line[5]);
						nodes.push_back(std::unique_ptr<day7::Node>(new day7::Node{ .dir_name = dir, .total_size = 0 }));
						stack.push_back(nodes.back().get());
					}
				}
			}
			else if (strncmp(&line[0], "dir", 3) != 0) // If not a dir, it's a file
			{
				char* context = nullptr;
				const size_t file_size = atoi(strtok_s(line.data(), " ", &context));
				const char* file_name = strtok_s(nullptr, " ", &context);
				for (day7::Node* node : stack)
				{
					node->total_size += file_size;
				}
			}
		}
		file.close();

		total_size_for_dir_to_delete_ = std::numeric_limits<size_t>::max();
		const size_t deletion_required = 30000000 - (70000000 - nodes[0]->total_size);

		for (const std::unique_ptr<day7::Node>& node : nodes)
		{
			log_.push_back(std::format("{}: {}", node->dir_name, node->total_size));
			if (node->total_size <= 100000)
			{
				total_size_for_under_100000_ += node->total_size;
			}
			if (node->total_size >= deletion_required)
			{
				total_size_for_dir_to_delete_ = std::min(total_size_for_dir_to_delete_, node->total_size);
			}
		}
	}

	void Day7::draw()
	{
		ImGui_print_log("Dir sizes##Day7Log", log_);
		ImGui_output_field("Total size of all directories of at most 100000", std::format("{}", total_size_for_under_100000_).c_str());
		ImGui_output_field("TOtal size for directory to delete", std::format("{}", total_size_for_dir_to_delete_).c_str());
	}
}