#include "day.h"

namespace aoc
{
	class Day1 final : public Day
	{
	public:
		static Day* create() { return new Day1(); }

		void run() override;
		void draw() override;

	private:
		int highest_total_ = 0;
		int highest_total_top_3_ = 0;

	};
}