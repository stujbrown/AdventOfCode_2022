#include "day.h"

#include <map>

namespace aoc
{
	class Day15 final : public Day
	{
	public:
		static Day* create() { return new Day15(); }

		void run() override;
		void draw() override;

	private:
		size_t num_safe_spots_on_row_ = 0;
		size_t tuning_frequency_ = 0;
	};
}