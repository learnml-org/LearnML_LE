#include <lml_le/message.hpp>

namespace lml_le
{
	message::message(LML_LE_LOG_BASE_PARAM, log_type type)
		: LML_LE_LOG_BASE_INIT(type, log_event::message)
	{}

	void message::save_prtd(std::ostream&) const
	{}
	void message::save_prtd_additional_data(std::ostream&) const
	{}

	log_ptr make_message(LML_LE_LOG_BASE_PARAM_MAKE_FUNC, log_type type)
	{
		return std::make_unique<lml_le::message>(LML_LE_LOG_BASE_INIT_MAKE_FUNC, type);
	}
}