#pragma once

#include <cstddef>

namespace lml_le
{
	void sor8_encrypt(char* dest, const char* src, std::size_t size, const char* key) noexcept;
	void sor8_decrypt(char* dest, const char* src, std::size_t size, const char* key) noexcept;
}