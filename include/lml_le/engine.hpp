#pragma once

#include <cstdint>

namespace lml_le
{
	extern std::uint64_t version;

	std::uint32_t initialize(std::uint64_t version) noexcept;
}