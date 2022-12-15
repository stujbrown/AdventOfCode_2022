#include "day.h"

namespace aoc
{
	class Day13 final : public Day
	{
	public:
		static Day* create() { return new Day13(); }

		void run() override;
		void draw() override;

	private:
		int sum_of_indices_ = 0;
		int sum_of_dividers_ = 0;
	};
}