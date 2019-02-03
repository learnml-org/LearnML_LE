#include <lml_le/internal_error.hpp>

namespace lml_le
{
	internal_error::internal_error(LML_LE_LOG_BASE_PARAM, std::uint32_t errorcode)
		: LML_LE_LOG_BASE_INIT(log_type::error, log_event::internal_error), errorcode(errorcode)
	{}

	void internal_error::save_prtd(std::ostream& stream) const
	{
		stream.write(reinterpret_cast<const char*>(&errorcode), sizeof(errorcode));
	}
	void internal_error::save_prtd_additional_data(std::ostream&) const
	{}

	log_ptr make_internal_error(LML_LE_LOG_BASE_PARAM_MAKE_FUNC, std::uint32_t errorcode)
	{
		return std::make_unique<internal_error>(LML_LE_LOG_BASE_INIT_MAKE_FUNC, errorcode);
	}
}