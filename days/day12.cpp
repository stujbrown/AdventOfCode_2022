#include "day12.h"
#include "output.h"

#include <fstream>
#include <string>

namespace aoc
{
	namespace day12
	{
		struct Node
		{
			std::pair<int, int> pos;
			Node* parent;
			int cost;
			int hueristic;
		};
	}

	bool update_if_in_container(std::vector<day12::Node*>& container, day12::Node* new_node, bool remove, day12::Node** out_node)
	{
		*out_node = nullptr;
		auto find_duplicate = [new_node](const day12::Node* n)
		{
			return n->pos == new_node->pos;
		};

		bool did_update = false;
		auto found = std::find_if(container.begin(), container.end(), find_duplicate);
		if (found != container.end())
		{
			auto entry = *found;

			if (entry->cost > new_node->cost)
			{
				entry->cost = new_node->cost;
				entry->parent = new_node->parent;
				did_update = true;

				if (remove)
				{
					container.erase(found);
				}
			}
			*out_node = entry;
		}
		return did_update;
	}

	void solve(const std::vector<char>& map, int map_width, int map_height, std::vector<std::pair<int, int>>& route, std::pair<int, int> start_pos, std::pair<int, int> end_pos)
	{
		const int movements[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} };

		std::vector<std::unique_ptr<day12::Node>> nodes;
		std::vector<day12::Node*> open;
		std::vector<day12::Node*> closed;
		nodes.push_back(std::unique_ptr<day12::Node>(new day12::Node{ .pos = start_pos, .hueristic = (int)('z' - 'a') }));
		open.push_back(nodes.back().get());
		while (!open.empty())
		{
			const auto current = open.back();
			open.pop_back();

			if (current->pos == end_pos)
			{
				day12::Node* head = current;
				while (head)
				{
					route.push_back(head->pos);
					head = head->parent;
				}
				break;
			}
			else
			{
				for (int i = 0; i < 4; ++i)
				{
					const std::pair<int, int> new_pos(current->pos.first + movements[i][0], current->pos.second + movements[i][1]);
					if (new_pos.first >= 0 && new_pos.first < map_width && new_pos.second >= 0 && new_pos.second < map_height)
					{
						const auto from_val = map[map_width * current->pos.second + current->pos.first];
						const auto to_val = map[map_width * new_pos.second + new_pos.first];

						if (to_val - from_val <= 1)
						{
							{
								int cost = current->cost + 1;
								int hueristic = 'z' - to_val;

								nodes.push_back(std::move(std::unique_ptr<day12::Node>(
									new day12::Node{ .pos = new_pos, .parent = current, .cost = cost, .hueristic = cost + hueristic })));
								day12::Node* new_node(nodes.back().get());

								day12::Node* found_node = nullptr;
								update_if_in_container(open, new_node, false, &found_node);
								if (found_node == nullptr)
								{
									const bool updated_closed_node = update_if_in_container(closed, new_node, true, &found_node);
									if (found_node == nullptr)
									{
										open.push_back(new_node);
									}
									else if (updated_closed_node)
									{
										open.push_back(found_node);
									}
								}
							}
						}
					}
				}

				closed.push_back(current);

				std::sort(open.begin(), open.end(), [](const day12::Node* l, const day12::Node* r) { return l->hueristic > r->hueristic; });
			}
		}
	}

	void Day12::run()
	{
		map_width_ = 0;
		map_height_ = 0;
		map_.clear();
		route_.clear();
		fewest_steps_ = std::numeric_limits<int>::max();

		std::ifstream file("inputs/day12.txt", std::ios_base::in);
		std::string line;
		while (std::getline(file, line) && (map_width_ == 0 || line.size() == map_width_))
		{
			map_width_ = map_width_ == 0 ? line.size() : map_width_;
			std::for_each_n(line.begin(), line.size(), [this](char c) { map_.push_back(c); });
			++map_height_;
		}
		file.close();

		auto start_itr = std::find(map_.begin(), map_.end(), 'S');
		auto end_itr = std::find(map_.begin(), map_.end(), 'E');
		const int start_index = std::distance(map_.begin(), start_itr);
		const int end_index = std::distance(map_.begin(), end_itr);
		start_pos_ = std::make_pair(start_index % map_width_, start_index / map_width_);
		end_pos_ = std::make_pair(end_index % map_width_, end_index / map_width_);
		*start_itr = 'a';
		*end_itr = 'z';

		solve(map_, map_width_, map_height_, route_, start_pos_, end_pos_);

		for (int y = 0; y < map_height_; ++y)
		{
			for (int x = 0; x < map_width_; ++x)
			{
				if (map_[map_width_ * y + x] == 'a')
				{
					std::vector<std::pair<int, int>> route;
					solve(map_, map_width_, map_height_, route, std::make_pair(x, y), end_pos_);
					if (route.size() != 0)
					{
						fewest_steps_ = std::min(fewest_steps_, (int)route.size() - 1);
					}
				}
			}
		}
	}

	void Day12::draw()
	{
		for (int y = 0; y < map_height_; ++y)
		{
			for (int x = 0; x < map_width_; ++x)
			{
				const bool is_path = std::find(route_.begin(), route_.end(), std::pair<int, int>(x, y)) != route_.end();
				ImGui::TextColored(is_path ? ImVec4(0.f, 1.f, 0.f, 1.f) : ImVec4(1.f, 1.f, 1.f, 1.f), "%c", map_[map_width_ * y + x]);
				if (x != map_width_ - 1)
					ImGui::SameLine();
			}
		}
		ImGui_output_field("Route length", std::format("{}", route_.size() - 1).c_str());
		ImGui_output_field("Fewest steps", std::format("{}", fewest_steps_).c_str());
	}
}