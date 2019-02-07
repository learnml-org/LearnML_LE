#include <lml_le/sor.hpp>

#include <lml_le/errorcode.hpp>

#include <cassert>
#include <cstring>
#include <fstream>

namespace lml_le
{
	void sor8_encrypt(char* dest, const char* src, std::size_t size, const char* key) noexcept
	{
		assert(key != nullptr);

		const std::size_t key_size = std::strlen(key);
		assert(key_size != 0);

		if (!src)
		{
			src = dest;
		}

		for (std::size_t i = 0; i < size; ++i)
		{
			*dest = *src + 30;
			
			for (std::size_t j = 0; j < key_size; ++j)
			{
				*dest ^= key[j];
			}

			*dest += 30;

			for (std::size_t j = 0; j < key_size; ++j)
			{
				*dest ^= key[key_size - j - 1];
			}

			++dest, ++src;
		}
	}
	void sor8_decrypt(char* dest, const char* src, std::size_t size, const char* key) noexcept
	{
		assert(key != nullptr);

		const std::size_t key_size = std::strlen(key);
		assert(key_size != 0);

		if (!src)
		{
			src = dest;
		}

		for (std::size_t i = 0; i < size; ++i)
		{
			*dest = *src;

			for (std::size_t j = 0; j < key_size; ++j)
			{
				*dest ^= key[j];
			}

			*dest -= 30;

			for (std::size_t j = 0; j < key_size; ++j)
			{
				*dest ^= key[key_size - j - 1];
			}

			*dest -= 30;

			++dest, ++src;
		}
	}
	void sor8_file(void(*func)(char*, const char*, std::size_t, const char*), const lml_pae::string& dest, const lml_pae::string& src, const char* key)
	{
		std::ifstream src_stream(src, std::ios::binary | std::ios::in);
		std::ofstream dest_stream(dest, std::ios::binary | std::ios::out);

		if (!src_stream) throw LML_LE_ERRORCODE_FAILED_TO_OPEN_FILE_SOR8ES;
		if (!dest_stream) throw LML_LE_ERRORCODE_FAILED_TO_OPEN_FILE_SOR8ED;

		char buffer[1024]{ 0, };

		while (!src_stream.eof())
		{
			src_stream.read(buffer, sizeof(buffer));
			std::size_t buffer_size = static_cast<std::size_t>(src_stream.gcount());
			func(buffer, nullptr, buffer_size, key);
			dest_stream.write(buffer, static_cast<std::streamsize>(buffer_size));
		}
	}
}