#include "day.h"

namespace aoc
{
	class Day7 final : public Day
	{
	public:
		static Day* create() { return new Day7(); }

		void run() override;
		void draw() override;

	private:
		size_t total_size_for_under_100000_ = 0;
		size_t total_size_for_dir_to_delete_ = 0;
	};
}