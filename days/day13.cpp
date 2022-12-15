#include "day13.h"
#include "output.h"

#include <fstream>
#include <string>
#include <stack>

namespace aoc
{
	namespace day13
	{
		class Value
		{
		public:
			int val_ = -1;
			std::vector<Value> list_;

			Value() {}
			Value(int val)
			{
				val_ = val;
			}

			inline bool operator==(const Value& right)
			{
				return compare(*this, right) == 0;
			}

			static int compare(const Value& left, const Value& right)
			{
				if (left.val_ != -1 && right.val_ != -1)
				{
					return left.val_ - right.val_;
				}
				else if (left.val_ != -1)
				{
					std::vector<Value> temp;
					temp.push_back(left.val_);
					return compare(temp, right.list_);
				}
				else if (right.val_ != -1)
				{
					std::vector<Value> temp;
					temp.push_back(right.val_);
					return compare(left.list_, temp);
				}

				return compare(left.list_, right.list_);
			}

			static int compare(const std::vector<Value>& left, const std::vector<Value>& right)
			{
				int i = 0;
				for (i = 0; i < left.size() && i < right.size(); ++i)
				{
					const int comparison = compare(left[i], right[i]);
					if (comparison > 0)
					{
						return 1;
					}
					if (comparison < 0)
					{
						return -1;
					}
				}
				return left.size() - right.size();
			}
		};
	}

	day13::Value make_divider(int val)
	{
		day13::Value inner(val);
		day13::Value outer;
		day13::Value outer2;
		outer.list_.push_back(inner);
		outer2.list_.push_back(outer);
		return outer2;
	}

	day13::Value read(const std::string& line)
	{
		std::stack<day13::Value> stack;
		int val_start_index = 0;

		auto try_read_int = [&stack, &line](int i, int val_start_index)
		{
			if (i - val_start_index > 0)
			{
				const int int_val = atoi(line.substr(val_start_index, i - val_start_index).c_str());
				stack.top().list_.push_back(day13::Value(int_val));

			}
		};

		for (size_t i = 0; i < line.size(); i++)
		{
			const char c = line[i];
			if (c == '[')
			{
				try_read_int(i, val_start_index);

				val_start_index = i + 1;
				stack.push(day13::Value());
			}
			else if (c == ']')
			{
				try_read_int(i, val_start_index);

				val_start_index = i + 1;
				const auto completed_val = std::move(stack.top());
				stack.pop();
				if (stack.empty())
				{
					return completed_val;
				}
				else
				{
					stack.top().list_.push_back(std::move(completed_val));
				}
			}
			else if (c == ',')
			{
				try_read_int(i, val_start_index);
				val_start_index = i + 1;
			}
		}

		return day13::Value();
	}

	void Day13::run()
	{
		std::ifstream file("inputs/day13.txt", std::ios_base::in);
		std::string line1, line2, empty_line;
		std::vector<day13::Value> packets;
		int index = 0;
		while (std::getline(file, line1) && std::getline(file, line2))
		{
			const auto left = read(line1);
			const auto right = read(line2);

			packets.push_back(left);
			packets.push_back(right);

			bool out_of_order = day13::Value::compare(left, right) > 0;
			log_.push_back(line1);
			log_.push_back(line2);
			log_.push_back(std::format("{}\n\n", out_of_order ? "out of order" : "in order"));
			sum_of_indices_ = out_of_order ? sum_of_indices_ : sum_of_indices_ + index + 1;

			std::getline(file, empty_line);
			++index;
		}

		const auto div1 = make_divider(2);
		const auto div2 = make_divider(6);

		packets.push_back(div1);
		packets.push_back(div2);

		std::sort(packets.begin(), packets.end(), [](const day13::Value& l, const day13::Value& r) -> bool
			{
				return day13::Value::compare(l, r) < 0;
			});

		const int index1 = std::distance(packets.begin(), std::find(packets.begin(), packets.end(), div1)) + 1;
		const int index2 = std::distance(packets.begin(), std::find(packets.begin(), packets.end(), div2)) + 1;
		sum_of_dividers_ = index1 * index2;
	}

	void Day13::draw()
	{
		ImGui_print_log("##day13log", log_);
		ImGui_output_field("Sum of indices", std::format("{}", sum_of_indices_).c_str());
		ImGui_output_field("Sum of dividers", std::format("{}", sum_of_dividers_).c_str());
	}
}