#pragma once

#include <lml_pae/string.hpp>

#include <cstddef>

namespace lml_le
{
	void sor8_encrypt(char* dest, const char* src, std::size_t size, const char* key) noexcept;
	void sor8_decrypt(char* dest, const char* src, std::size_t size, const char* key) noexcept;
	void sor8_file(void(*func)(char*, const char*, std::size_t, const char*), const lml_pae::string& dest, const lml_pae::string& src, const char* key);
}