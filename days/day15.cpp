#include "day15.h"
#include "output.h"

#include <fstream>
#include <string>
#include <set>

namespace aoc
{
	void Day15::run()
	{
		struct Sensor
		{
			std::pair<int, int> sensor_pos_ = std::make_pair(0, 0);
			int safe_range_ = 0;
		};

		num_safe_spots_on_row_ = 0;
		tuning_frequency_ = 0;

		std::vector<Sensor> sensors;

		std::ifstream file("inputs/day15.txt", std::ios_base::in);
		std::string line;
		while (std::getline(file, line))
		{
			char* context = nullptr;
			(void)strtok_s(line.data(), "=", &context);
			const int sensor_x = atoi(strtok_s(nullptr, ",", &context));
			(void)strtok_s(nullptr, "=", &context);
			const int sensor_y = atoi(strtok_s(nullptr, ":", &context));
			(void)strtok_s(nullptr, "=", &context);
			const int beacon_x = atoi(strtok_s(nullptr, ",", &context));
			(void)strtok_s(nullptr, "=", &context);
			const int beacon_y = atoi(strtok_s(nullptr, ",", &context));

			const int safe_range = abs(sensor_x - beacon_x) + abs(sensor_y - beacon_y);
			sensors.push_back(Sensor{
				.sensor_pos_ = std::make_pair(sensor_x, sensor_y),
				.safe_range_ = safe_range });

				}
		file.close();

		std::set<std::pair<int, int>> possible_spots;

		const int target_line = 2000000;
		std::vector<std::pair<int, int>> ranges;
		for (const auto& sensor : sensors)
		{
			const int falloff = abs(target_line - sensor.sensor_pos_.second);
			const auto new_range = std::make_pair((sensor.sensor_pos_.first - sensor.safe_range_) + falloff,
				(sensor.sensor_pos_.first + sensor.safe_range_) - falloff);

			if (new_range.first <= new_range.second)
			{
				ranges.push_back(new_range);
			}

			int x = sensor.sensor_pos_.first;
			int y = sensor.sensor_pos_.second + sensor.safe_range_ + 1;
			while (x != sensor.sensor_pos_.first - (sensor.safe_range_ + 1))
			{
				possible_spots.insert(std::make_pair(x, y));
				--x;
				--y;
			}
			while (y != sensor.sensor_pos_.second - (sensor.safe_range_ + 1))
			{
				possible_spots.insert(std::make_pair(x, y));
				++x;
				--y;
			}
			while (x != sensor.sensor_pos_.first + (sensor.safe_range_ + 1))
			{
				possible_spots.insert(std::make_pair(x, y));
				++x;
				++y;
			}
			while (y != sensor.sensor_pos_.second + (sensor.safe_range_ + 1))
			{
				possible_spots.insert(std::make_pair(x, y));
				--x;
				++y;
			}
		}

		auto spot_itr = possible_spots.begin();
		while (spot_itr != possible_spots.end())
		{
			bool is_valid = true;
			if (spot_itr->first < 0 || spot_itr->second < 0 || spot_itr->first > 4000000 || spot_itr->second > 4000000)
			{
				is_valid = false;
			}
			else
			{
				for (const auto& sensor : sensors)
				{
					if ((abs(spot_itr->first - sensor.sensor_pos_.first) + abs(spot_itr->second - sensor.sensor_pos_.second))
						<= sensor.safe_range_)
					{
						is_valid = false;
						break;
					}
				}
			}

			if (!is_valid)
				spot_itr = possible_spots.erase(spot_itr);
			else
				++spot_itr;
		}


		bool did_combine = false;
		do
		{
			did_combine = false;
			for (int i = 0; i < ranges.size(); ++i)
			{
				for (int j = 0; j < ranges.size(); ++j)
				{
					if (i != j)
					{
						auto& range = ranges[i];
						const auto& other_range = ranges[j];
						if (!(other_range.second < range.first || other_range.first > range.second))
						{
							range.first = std::min(range.first, other_range.first);
							range.second = std::max(range.second, other_range.second);
							ranges.erase(ranges.begin() + j);

							did_combine = true;
							i = ranges.size();
							j = ranges.size();
						}
					}
				}
			}
		} while (did_combine);

		for (const auto& range : ranges)
		{
			num_safe_spots_on_row_ += (range.second - range.first);
		}

		const auto& spot = *possible_spots.begin();
		tuning_frequency_ = (size_t)(spot.first * (size_t)4000000) + (size_t)spot.second;
	}

	void Day15::draw()
	{
		ImGui_output_field("Num spots without possible beacons on row 2000000", std::format("{}", num_safe_spots_on_row_).c_str());
		ImGui_output_field("Tuning frequency", std::format("{}", tuning_frequency_).c_str());
	}
}