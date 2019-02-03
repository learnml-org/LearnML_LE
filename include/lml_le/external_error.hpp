#pragma once

#include <lml_le/log.hpp>

#include <exception>

namespace lml_le
{
	class external_error final : public log
	{
	public:
		external_error(LML_LE_LOG_BASE_PARAM, const std::exception& exception);
		external_error(const external_error&) = delete;
		virtual ~external_error() override = default;

	public:
		external_error& operator=(const external_error&) = delete;

	protected:
		virtual void save_prtd(std::ostream& stream) const override;
		virtual void save_prtd_additional_data(std::ostream& stream) const override;

	public:
		std::exception exception;
	};

	log_ptr make_external_error(LML_LE_LOG_BASE_PARAM_MAKE_FUNC, const std::exception& exception);
}