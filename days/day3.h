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

	};
}