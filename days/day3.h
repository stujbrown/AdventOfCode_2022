#include "day.h"

namespace aoc
{
	class Day3 final : public Day
	{
	public:
		static Day* create() { return new Day3(); }

		void run() override;
		void draw() override;

	private:
		int duplicate_priority_total_ = 0;
		int group_badge_total_ = 0;
	};
}