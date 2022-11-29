#pragma once

#include "day_entry.h"

#include <vector>

bool window_create();
void window_run(std::vector<DayEntry>&& day_functions);
void window_cleanup();