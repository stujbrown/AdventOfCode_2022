#include "aoc_days.h"

namespace aoc
{
	class Day1 final : public Day
	{
	public:
		static Day* create() { return new Day1(); }

		void run() override;
		void draw() override;
	};
}