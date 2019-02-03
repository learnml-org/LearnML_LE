#include <lml_le/engine.hpp>

namespace lml_le
{
	std::uint32_t initialize(std::uint64_t version) noexcept
	{
		lml_le::version = version;

		return 0;
	}
}