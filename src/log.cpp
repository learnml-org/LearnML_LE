#include <lml_le/log.hpp>

#include <lml_le/engine.hpp>
#include <lml_le/errorcode.hpp>
#include <lml_le/sor.hpp>
#include <lml_pae/architecture.hpp>
#include <lml_pae/filesystem.hpp>
#include <lml_pae/os.hpp>
#include <lml_pae/string.hpp>

#include <fstream>
#include <thread>
#include <utility>

namespace lml_le
{
	log::log(log_type type, log_event event, const lml_pae::string& message, std::chrono::system_clock::time_point time)
		: type(type), event(event), message(message), time(time)
	{}

	void log::save(std::ostream& stream, bool include_additional_data) const
	{
		stream.write(reinterpret_cast<const char*>(&type), sizeof(type));
		stream.write(reinterpret_cast<const char*>(&event), sizeof(event));
		
		const std::uint64_t message_size = static_cast<std::uint64_t>(message.size());
		stream.write(reinterpret_cast<const char*>(&message_size), sizeof(message_size));
		const std::string message_utf8 = lml_pae::to_utf8(message);
		stream.write(message_utf8.c_str(), static_cast<std::streamsize>(message_size));

		const std::int64_t time = this->time.time_since_epoch().count();
		stream.write(reinterpret_cast<const char*>(&time), sizeof(time));

		save_prtd(stream);
		
		if (include_additional_data)
		{
			save_prtd_additional_data(stream);
		}
	}
}

namespace lml_le
{
	logger::~logger()
	{
		if (!autosave_.empty())
		{
			save(autosave_, autosave_include_additional_data_);
		}
	}

	void logger::add_log(log_ptr&& log)
	{
		logs_.push_back(std::move(log));
	}

	void logger::save(const lml_pae::string& path) const
	{
		save(path, false);
	}
	void logger::save(const lml_pae::string& path, bool include_additional_data) const
	{
		const lml_pae::string temp_path = lml_pae::get_temp_file();

		std::ofstream stream(temp_path);
		for (int i = 0; i < 6 && !stream; ++i)
		{
			using namespace std::chrono_literals;

			if (i == 5) throw LML_LE_ERRORCODE_FAILED_TO_SAVE_LOG;

			stream.open(path);
			std::this_thread::sleep_for(0.5s);
		}

		static constexpr char magic_number[] = { 'L', 'M', 'L', 'L' };
		static constexpr std::uint32_t version = 0;
		static constexpr std::uint32_t bom = 0x12345678;

		// Header (64 Bytes)
		stream.write(magic_number, sizeof(magic_number));															// Magic Number				(4 Bytes)
		stream.write(reinterpret_cast<const char*>(&version), sizeof(version));										// Log System Veresion		(4 Bytes)
		stream.write(reinterpret_cast<const char*>(&bom), sizeof(bom));												// Byte Order Mark			(4 Bytes)
		stream.write(reinterpret_cast<const char*>(&include_additional_data), sizeof(include_additional_data));		//							(1 Bytes)
		stream.write(reinterpret_cast<const char*>(&lml_le::version), sizeof(lml_le::version));						// Application Version		(8 Bytes)
		
		std::uint8_t buffer_u8 = static_cast<std::uint8_t>(lml_pae::architecture::target);
		stream.write(reinterpret_cast<const char*>(&buffer_u8), sizeof(buffer_u8));									// Platform Architecture	(1 Bytes)
		buffer_u8 = static_cast<std::uint8_t>(lml_pae::os::target);
		stream.write(reinterpret_cast<const char*>(&buffer_u8), sizeof(buffer_u8));									// Platform OS				(1 Bytes)
		const std::string os_info = lml_pae::get_os_info();
		const std::uint64_t os_info_size = static_cast<std::uint64_t>(os_info.size());
		stream.write(reinterpret_cast<const char*>(&os_info_size), sizeof(os_info_size));							// Platform OS Info Size	(8 Bytes)
		stream.write(os_info.c_str(), static_cast<std::streamsize>(os_info_size));									// Platform OS Info

		// Logs
		const std::uint64_t count_of_logs(logs_.size());
		stream.write(reinterpret_cast<const char*>(&count_of_logs), sizeof(count_of_logs));							//							(8 Bytes)
		
		for (const log_ptr& l : logs_)
		{
			l->save(stream, include_additional_data);
		}

		stream.close();
		sor8_file(sor8_encrypt, path, temp_path, "LearnML Logging Engine");
	}

	lml_pae::string logger::autosave() const
	{
		return autosave_;
	}
	void logger::autosave(const lml_pae::string& new_autosave)
	{
		autosave_ = new_autosave;
	}
	bool logger::autosave_include_additional_data() const noexcept
	{
		return autosave_include_additional_data_;
	}
	void logger::autosave_include_additional_data(bool new_autosave_include_additional_data) noexcept
	{
		autosave_include_additional_data_ = new_autosave_include_additional_data;
	}
}