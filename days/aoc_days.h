#pragma once

namespace aoc
{
	class Day
	{
	public:
		virtual ~Day() {}

		virtual void run() = 0;
		virtual void draw() = 0;
	};
}