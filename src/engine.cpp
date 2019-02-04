#include <lml_le/engine.hpp>

#include <limits>

namespace lml_le
{
#undef max
	std::uint64_t version = std::numeric_limits<std::uint64_t>::max();
	std::basic_string<TCHAR>(*get_temp_file)() = nullptr;

	std::uint32_t initialize(std::uint64_t version, std::basic_string<TCHAR>(*get_temp_file)()) noexcept
	{
		lml_le::version = version;
		lml_le::get_temp_file = get_temp_file;

		return 0;
	}
}