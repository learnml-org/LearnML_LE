#include <lml_le/sor.hpp>

#include <cassert>
#include <cstring>

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
}