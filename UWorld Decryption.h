#pragma once
#include <cstdint>
#include <algorithm>

inline uint64_t DecryptUworld(uint64_t value)
{
    return (value ^ 0xFFFFFFFFD599D092ULL) + 0x248ULL;
}

uintptr_t encryptedUWorld = Memory::Read<uintptr_t>(Kernel::state.process_base + offsets::UWorld);
uintptr_t decryptedUWorld = DecryptUworld(encryptedUWorld);

Cached.UWorld = decryptedUWorld;
