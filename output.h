#pragma once

#include "imgui.h"

#include <memory>
#include <format>

void ImGui_output_field(const char* label, const char* value)
{
	const size_t val_length = strlen(value);
	char* val_str = (char*)_malloca(val_length + 1);

	sprintf_s(val_str, val_length + 1, "%s", value);
	ImGui::Text(label);
	ImGui::SameLine();
	ImGui::InputText(std::format("##{}", label).c_str(), val_str, val_length + 1);

}