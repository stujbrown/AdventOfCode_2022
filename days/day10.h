#include "day.h"

#include <array>

namespace aoc
{
	class Day10 final : public Day
	{
	public:
		static Day* create() { return new Day10(); }

		void run() override;
		void draw() override;

	private:
		static const int screen_width = 40;
		static const int screen_height = 6;

		int signal_sum_ = 0;
		std::array<bool, screen_width * screen_height> pixel_display_;
	};
}