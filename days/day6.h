#include "day.h"

namespace aoc
{
	class Day6 final : public Day
	{
	public:
		static Day* create() { return new Day6(); }

		void run() override;
		void draw() override;

	private:
		int packet_marker_end_index_ = 0;
		int message_marker_end_index_ = 0;
	};
}