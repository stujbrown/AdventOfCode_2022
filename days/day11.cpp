#include "day11.h"
#include "output.h"

#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <ranges>

namespace aoc
{
	size_t calc_monkey_business(std::vector<std::string>& log, int num_rounds, bool divide)
	{
		struct Monkey
		{
			std::function<size_t(size_t)> op_function_;
			std::vector<size_t> items_;
			size_t test_value_ = 0;
			size_t test_target_true_ = 0;
			size_t test_target_false_ = 0;
			size_t inspection_count_ = 0;
		};

		std::vector<Monkey> monkeys;

		std::ifstream file("inputs/day11.txt", std::ios_base::in);
		std::string line;
		while (std::getline(file, line))
		{
			if (line.compare(0, 6, "Monkey") == 0)
			{
				auto new_monkey = Monkey();

				std::getline(file, line);
				char* item_string = &line[line.find(": ") + 2];

				char* context = nullptr;
				const char* item = strtok_s(item_string, ",", &context);
				while (item)
				{
					new_monkey.items_.push_back(atoi(item));
					item = strtok_s(nullptr, ",", &context);
				}

				std::getline(file, line);
				const char* op_string = &line[line.find("old ") + 4];
				const bool is_mul = op_string[0] == '*';
				const bool is_with_old_value = strcmp(&op_string[2], "old") == 0;
				const size_t other_val = atoi(&op_string[2]);
				new_monkey.op_function_ = [is_mul, is_with_old_value, other_val](size_t old) -> size_t
				{
					const size_t val = is_with_old_value ? old : other_val;
					return is_mul ? (old * val) : (old + val);
				};

				std::getline(file, line);
				new_monkey.test_value_ = atoi(&line[line.find("by ") + 3]);

				std::getline(file, line);
				new_monkey.test_target_true_ = atoi(&line[line.find("monkey ") + 7]);
				std::getline(file, line);
				new_monkey.test_target_false_ = atoi(&line[line.find("monkey ") + 7]);
				std::getline(file, line);
				monkeys.push_back(new_monkey);
			}
		}
		file.close();

		size_t common_divisor = monkeys[0].test_value_;
		for (int i = 1; i < monkeys.size(); ++i)
		{
			common_divisor *= monkeys[i].test_value_;
		}

		for (auto round = 0; round < num_rounds; ++round)
		{
			log.push_back(std::format("\nRound {}", round));
			for (auto monkey_index = 0; monkey_index < monkeys.size(); ++monkey_index)
			{
				auto& monkey = monkeys[monkey_index];
				for (auto item_index = 0; item_index < monkey.items_.size(); ++item_index)
				{
					++monkey.inspection_count_;
					const size_t new_val = monkey.op_function_(monkey.items_[item_index]);
					const size_t new_worry_level = divide ? new_val / 3 : new_val % common_divisor;
					const bool test_result = new_worry_level % monkey.test_value_ == 0;
					if (test_result)
						monkeys[monkey.test_target_true_].items_.push_back(new_worry_level);
					else
						monkeys[monkey.test_target_false_].items_.push_back(new_worry_level);

					log.push_back(std::format("Monkey {}: Inspects {}, new level {}, passed: {}", monkey_index, monkey.items_[item_index], new_worry_level, test_result));
				}
				monkey.items_.clear();
			}
		}

		std::sort(monkeys.begin(), monkeys.end(), [](const Monkey& l, const Monkey& r) -> bool { return l.inspection_count_ > r.inspection_count_; });
		return monkeys[0].inspection_count_ * monkeys[1].inspection_count_;
	}

	void Day11::run()
	{
		monkey_busness_Level_ = calc_monkey_business(log_, 20, true);
		monkey_busness_level_2_ = calc_monkey_business(log_, 10000, false);
	}

	void Day11::draw()
	{
		ImGui_print_log("##Day11Log", log_);
		ImGui_output_field("Level of monkey business", std::format("{}", monkey_busness_Level_).c_str());
		ImGui_output_field("Level of elevated monkey business", std::format("{}", monkey_busness_level_2_).c_str());
	}
}