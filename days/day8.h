#include "day.h"

namespace aoc
{
	class Day8 final : public Day
	{
	public:
		static Day* create() { return new Day8(); }

		void run() override;
		void draw() override;

	private:
		std::vector<std::string> grid_;
		std::vector<bool> visible_states_;
		int total_visible_ = 0;
		size_t highest_score_ = 0;
	};
}