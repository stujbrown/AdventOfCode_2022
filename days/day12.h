#include "day.h"

#include <vector>

namespace aoc
{
	class Day12 final : public Day
	{
	public:
		static Day* create() { return new Day12(); }

		void run() override;
		void draw() override;

	private:
		std::pair<int, int> start_pos_;
		std::pair<int, int> end_pos_;
		int map_width_ = 0;
		int map_height_ = 0;
		std::vector<char> map_;
		std::vector<std::pair<int, int>> route_;
		int fewest_steps_ = 0;
	};
}