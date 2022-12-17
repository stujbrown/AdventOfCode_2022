#include "day.h"
#include <map>

namespace aoc
{
	class Day14 final : public Day
	{
	public:
		struct Sim
		{
			std::pair<int, int> lowest_coordinate_ = std::make_pair(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
			std::pair<int, int> highest_coordinate_ = std::make_pair(0, 0);
			std::map<std::pair<int, int>, char> cave_;

			int units_of_sand_ = 0;
		};

		static Day* create() { return new Day14(); }

		void run() override;
		void draw() override;

	private:
		Sim no_floor_simulation_;
		Sim final_simulation_;
	};
}