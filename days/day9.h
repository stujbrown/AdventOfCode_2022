#include "day.h"

#include <set>

namespace aoc
{
	class Day9 final : public Day
	{
	public:
		static Day* create() { return new Day9(); }

		void run() override;
		void draw() override;

	private:
		std::set<std::pair<int, int>> short_tail_visits_;
		std::set<std::pair<int, int>> long_tail_visits_;
	};
}