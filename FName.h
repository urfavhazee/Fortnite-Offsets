#pragma once
#include "includes.h"

namespace FName
{
    constexpr uint64_t NAMES_TABLE_RVA = 0x17A50D00;
    constexpr uint64_t CHUNK_OFFSET_BASE = 0xDF2;
    
    constexpr uint32_t INDEX_XOR_KEY = 0xA426EB57;
    constexpr uint32_t STRING_SEED_MULTIPLIER = 8312;
    constexpr uint32_t STRING_SEED_BASE = 1055325479;
    constexpr uint8_t STRING_XOR_OFFSET = 14;
    
    constexpr uint16_t LENGTH_MASK = 0x3FF;
    constexpr uint16_t LENGTH_XOR_MASK = 0x3FB;
    constexpr uint16_t REDIRECT_MARKER = 1019;
    constexpr uint16_t MAX_STRING_LENGTH = 255;
    constexpr uint8_t HEADER_SIZE = 2;
    constexpr uint8_t CHUNK_SHIFT = 16;
    constexpr uint8_t MAX_RETRY_COUNT = 5;

    int32_t DecryptIndex(int32_t encrypted_index)
    {
        if (encrypted_index == 0)
            return 0;

        uint32_t decrypted = (encrypted_index - 1) ^ INDEX_XOR_KEY;
        
        if (decrypted == 0xFFFFFFFF)
            return 0;

        return decrypted + 1;
    }

    void DecryptFName(char* str_buffer, int32_t str_length)
    {
        if (str_length <= 0)
            return;

        unsigned int cipher_seed = STRING_SEED_MULTIPLIER * str_length + STRING_SEED_BASE;

        for (int i = 0; i < str_length; i++)
        {
            str_buffer[i] ^= static_cast<uint8_t>(cipher_seed + STRING_XOR_OFFSET);
            cipher_seed = STRING_SEED_MULTIPLIER * cipher_seed + STRING_SEED_BASE;
        }
    }

    string ToString(int32_t name_index)
    {
        int32_t current_index = DecryptIndex(name_index);
        int attempts = 0;

    ResolveEntry:
        if (current_index <= 0 || attempts > MAX_RETRY_COUNT)
            return "";

        const uint64_t chunk_id = static_cast<uint64_t>(current_index >> CHUNK_SHIFT) + CHUNK_OFFSET_BASE;
        const uintptr_t chunk_address = Memory::Read<uint64_t>(
            Kernel::state.process_base + NAMES_TABLE_RVA + (chunk_id * sizeof(uint64_t))
        );

        if (!chunk_address)
            return "";

        const uintptr_t entry_address = chunk_address + (HEADER_SIZE * static_cast<uint16_t>(current_index));
        const uint16_t entry_header = Memory::Read<uint16_t>(entry_address);
        const uint16_t raw_length = (entry_header >> 1) & LENGTH_MASK;

        // Check for redirect entry
        if (raw_length == REDIRECT_MARKER)
        {
            current_index = DecryptIndex(Memory::Read<int32_t>(entry_address + HEADER_SIZE));
            attempts++;
            goto ResolveEntry;
        }

        const uint16_t actual_length = raw_length ^ LENGTH_XOR_MASK;

        if (actual_length == 0 || actual_length > MAX_STRING_LENGTH)
            return "";

        char name_buffer[MAX_STRING_LENGTH + 1];

        for (uint16_t i = 0; i < actual_length && i < MAX_STRING_LENGTH; i++)
        {
            name_buffer[i] = Memory::Read<char>(entry_address + HEADER_SIZE + i);
        }

        name_buffer[actual_length] = '\0';
        DecryptFName(name_buffer, actual_length);

        return string(name_buffer, actual_length);
    }

    string GetFname(int32_t name_index)
    {
        return ToString(name_index);
    }
}
