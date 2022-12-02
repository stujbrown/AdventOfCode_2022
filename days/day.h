#pragma once

#include <vector>
#include <string>

namespace aoc
{
	class Day
	{
	public:
		virtual ~Day() {}

		virtual void run() = 0;
		virtual void draw() = 0;

		const std::vector<std::string>& get_log() const { return log_; }

	protected:
		std::vector<std::string> log_;
	};
}