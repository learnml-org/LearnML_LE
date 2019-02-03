#pragma once

#include <lml_le/log.hpp>

namespace lml_le
{
	class message final : public log
	{
	public:
		message(LML_LE_LOG_BASE_PARAM, log_type type);
		message(const message&) = delete;
		virtual ~message() override = default;

	public:
		message& operator=(const message&) = delete;

	protected:
		virtual void save_prtd(std::ostream& stream) const override;
		virtual void save_prtd_additional_data(std::ostream& stream) const override;
	};

	log_ptr make_message(LML_LE_LOG_BASE_PARAM_MAKE_FUNC, log_type type);
}