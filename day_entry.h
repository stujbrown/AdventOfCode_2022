#pragma once

#include "days/aoc_days.h"

#include <string>
#include <functional>
#include <memory>

class DayEntry
{
public:
	DayEntry(std::string name, std::function<aoc::Day*()> factory)
	{
		name_ = move(name);
		factory_ = move(factory);
	}

	inline const char* name() const { return name_.c_str(); }

	void run()
	{
		 day_ = std::unique_ptr<aoc::Day>(factory_());
		 day_->run();
	}

	void draw()
	{
		if (day_ != nullptr)
		{
			day_->draw();
		}
	}

private:
	std::function<aoc::Day* ()> factory_;
	std::string name_;
	std::unique_ptr<aoc::Day> day_;
};