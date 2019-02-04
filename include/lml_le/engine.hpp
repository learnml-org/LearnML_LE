#pragma once

#include <cstdint>
#include <string>
#include <Windows.h>

namespace lml_le
{
	extern std::uint64_t version;
	extern std::basic_string<TCHAR>(*get_temp_file)();

	std::uint32_t initialize(std::uint64_t version, std::basic_string<TCHAR>(*get_temp_file)()) noexcept;
}