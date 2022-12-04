#include "day.h"

namespace aoc
{
	class Day4 final : public Day
	{
	public:
		static Day* create() { return new Day4(); }

		void run() override;
		void draw() override;

	private:
		int contained_pair_total_ = 0;
		int overlapped_pair_total_ = 0;
	};
}