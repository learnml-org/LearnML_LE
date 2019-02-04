#pragma once

#include <cstdint>

#define LML_LE_ERRORCODE_FAILED_TO_SAVE_LOG						static_cast<std::uint32_t>(0x00020000)

#define LML_LE_ERRORCODE_FAILED_TO_ENCODE_16TO8					static_cast<std::uint32_t>(0x00020010)
#define LML_LE_ERRORCODE_FAILED_TO_ENCODE_DTO8					static_cast<std::uint32_t>(0x00020011)
#define LML_LE_ERRORCODE_FAILED_TO_ENCODE_16TOD					static_cast<std::uint32_t>(0x00020012)
#define LML_LE_ERRORCODE_FAILED_TO_ENCODE_8TOD					static_cast<std::uint32_t>(0x00020013)