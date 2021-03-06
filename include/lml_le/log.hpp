#pragma once

#include <lml_pae/string.hpp>

#include <cstdint>
#include <chrono>
#include <exception>
#include <optional>
#include <ostream>
#include <memory>
#include <string>
#include <vector>

namespace lml_le
{
	enum class log_type
	{
		none,

		info,
		warning,
		error,
	};

	enum class log_event
	{
		none,

		message,
		internal_error,
		external_error,
	};

	class log
	{
	public:
		log(const log&) = delete;
		virtual ~log() = default;

	protected:
		log(log_type type, log_event event, const lml_pae::string& message, std::chrono::system_clock::time_point time);

	public:
		log& operator=(const log&) = delete;
		
	public:
		void save(std::ostream& stream, bool include_additional_data) const;

	protected:
		virtual void save_prtd(std::ostream& stream) const = 0;
		virtual void save_prtd_additional_data(std::ostream& stream) const = 0;

	public:
		log_type type = log_type::none;
		log_event event = log_event::none;
		lml_pae::string message;
		std::chrono::system_clock::time_point time;
	};

	using log_ptr = std::unique_ptr<log>;

#define LML_LE_LOG_BASE_PARAM				const lml_pae::string& message, std::chrono::system_clock::time_point time
#define LML_LE_LOG_BASE_PARAM_MAKE_FUNC		const lml_pae::string& message
#define LML_LE_LOG_BASE_INIT(type, event)	log(type, event, message, time)
#define LML_LE_LOG_BASE_INIT_MAKE_FUNC		message, std::chrono::system_clock::now()

	class logger final
	{
	public:
		logger() noexcept = default;
		logger(const logger&) = delete;
		~logger();

	public:
		logger& operator=(const logger&) = delete;

	public:
		void add_log(log_ptr&& log);
		
		void save(const lml_pae::string& path) const;
		void save(const lml_pae::string& path, bool include_additional_data) const;

	public:
		lml_pae::string autosave() const;
		void autosave(const lml_pae::string& new_autosave);
		bool autosave_include_additional_data() const noexcept;
		void autosave_include_additional_data(bool new_autosave_include_additional_data) noexcept;

	private:
		std::vector<log_ptr> logs_;
		lml_pae::string autosave_;
		bool autosave_include_additional_data_;
	};
}