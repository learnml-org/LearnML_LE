#pragma once

#include <cstddef>
#include <string>
#include <Windows.h>

namespace lml_le
{
	void sor8_encrypt(char* dest, const char* src, std::size_t size, const char* key) noexcept;
	void sor8_decrypt(char* dest, const char* src, std::size_t size, const char* key) noexcept;
	void sor8_file(void(*func)(char*, const char*, std::size_t, const char*), const std::basic_string<TCHAR>& dest, const std::basic_string<TCHAR>& src, const char* key);
}