#include "day.h"

namespace aoc
{
	class Day2 final : public Day
	{
	public:
		static Day* create() { return new Day2(); }

		void run() override;
		void draw() override;

	private:
		int total_score_response_as_types_ = 0;
		int total_score_response_as_results_ = 0;

	};
}