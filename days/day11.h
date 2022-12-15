#include "day.h"

namespace aoc
{
	class Day11 final : public Day
	{
	public:
		static Day* create() { return new Day11(); }

		void run() override;
		void draw() override;

	private:
		size_t monkey_busness_Level_;
		size_t monkey_busness_level_2_;
	};
}