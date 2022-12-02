#pragma once

#include "days/day.h"

#include <string>
#include <functional>
#include <memory>

class DayEntry
{
public:
	DayEntry(std::string name, std::function<aoc::Day* ()> factory)
	{
		name_ = move(name);
		factory_ = move(factory);
	}

	inline const char* name() const { return name_.c_str(); }
	inline void set_duration(uint64_t duration_ns) { last_duration_ns_ = duration_ns; }
	inline uint64_t last_duration() const { return last_duration_ns_; }

	inline void run()
	{
		day_ = std::unique_ptr<aoc::Day>(factory_());
		day_->run();
	}

	inline void draw()
	{
		if (day_ != nullptr)
		{
			day_->draw();
		}
	}

	/// <summary>
	/// Mark as touched and return true if this is the first time.
	/// </summary>
	inline bool touch()
	{
		bool has_been_touched = has_been_touched_;
		has_been_touched_ = true;
		return !has_been_touched;
	}

private:
	std::function<aoc::Day* ()> factory_;
	std::string name_;
	std::unique_ptr<aoc::Day> day_;

	bool has_been_touched_ = false;
	uint64_t last_duration_ns_ = 0;
};