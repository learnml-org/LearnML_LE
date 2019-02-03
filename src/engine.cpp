#include <lml_le/engine.hpp>

#include <limits>

namespace lml_le
{
	std::uint64_t version = std::numeric_limits<std::uint64_t>::max();

	std::uint32_t initialize(std::uint64_t version) noexcept
	{
		lml_le::version = version;

		return 0;
	}
}