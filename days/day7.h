#include "day.h"

namespace aoc
{
	class Day? final : public Day
	{
	public:
		static Day* create() { return new Day?(); }

		void run() override;
		void draw() override;

	private:

	};
}