#include "day.h"

namespace aoc
{
	class Day5 final : public Day
	{
	public:
		static Day* create() { return new Day5(); }

		void run() override;
		void draw() override;

	private:
		static void record_debug_stacks(const std::vector<std::vector<char>>& stacks, size_t& height_counter, std::vector<std::vector<float>>& output);

		void run_for_crane(bool is_crane2, std::vector<char>& out_top_items);

		std::vector<char> crane1_top_items_;
		std::vector<char> crane2_top_items_;

		size_t highest_value_ = 0;
		std::vector<std::vector<float>> debug_stack_values_;
	};
}