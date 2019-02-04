#pragma once

#include <cstdint>

#define LML_LE_ERRORCODE_FAILED_TO_SAVE_LOG						static_cast<std::uint32_t>(0x00020000)

#define LML_LE_ERRORCODE_FAILED_TO_ENCODE_16TO8					static_cast<std::uint32_t>(0x00020010)
#define LML_LE_ERRORCODE_FAILED_TO_ENCODE_DTO8					static_cast<std::uint32_t>(0x00020011)
#define LML_LE_ERRORCODE_FAILED_TO_ENCODE_16TOD					static_cast<std::uint32_t>(0x00020012)
#define LML_LE_ERRORCODE_FAILED_TO_ENCODE_8TOD					static_cast<std::uint32_t>(0x00020013)

#define LML_LE_ERRORCODE_FAILED_TO_OPEN_FILE_SOR8ES				static_cast<std::uint32_t>(0x00020020)
#define LML_LE_ERRORCODE_FAILED_TO_OPEN_FILE_SOR8ED				static_cast<std::uint32_t>(0x00020021)
#define LML_LE_ERRORCODE_FAILED_TO_OPEN_FILE_SOR8DS				static_cast<std::uint32_t>(0x00020022)
#define LML_LE_ERRORCODE_FAILED_TO_OPEN_FILE_SOR8DD				static_cast<std::uint32_t>(0x00020023)