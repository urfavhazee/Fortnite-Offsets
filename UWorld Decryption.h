#pragma once
#include <cstdint>
#include <algorithm>

inline uint64_t DecryptUworld(uint64_t gworld)
{
    return ~std::rotl(gworld ^ 0x7B40E797ULL, 50);
}
uintptr_t encryptedUWorld = Memory::Read<uintptr_t>(Kernel::state.process_base + offsets::UWorld);
uintptr_t decryptedUWorld = DecryptUworld(encryptedUWorld);

Cached.UWorld = decryptedUWorld;