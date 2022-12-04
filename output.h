#pragma once

#include "imgui.h"

#include <memory>
#include <format>

inline bool list_item_callback(void* data, int idx, const char** out_text)
{
	const auto* list = (const std::vector<std::string>*)data;
	*out_text = (*list)[idx].c_str();
	return true;
}

inline void ImGui_output_field(const char* label, const char* value)
{
	const size_t val_length = strlen(value);
	char* val_str = (char*)_malloca(val_length + 1);
	if (val_str != nullptr)
	{
		strncpy_s(val_str, val_length + 1, value, val_length + 1);
	}

	ImGui::Text(label);
	ImGui::SameLine();
	ImGui::InputText(std::format("##{}", label).c_str(), val_str, val_length + 1);
}

inline void ImGui_print_log(const char* id, const std::vector<std::string>& log)
{
	ImGui::Spacing();

	int selected = -1;
	ImGui::ListBox(id, &selected,
		list_item_callback,
		(void*)&log,
		static_cast<int>(log.size()));

	ImGui::Spacing();
}

