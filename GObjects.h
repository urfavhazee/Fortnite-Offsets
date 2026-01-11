namespace GObjects
{
    constexpr uintptr_t GOBJECTS_COUNT_RVA = 0x17B2DC64;
    constexpr uintptr_t GOBJECTS_PTR_RVA = 0x17B2DC58;
    
    constexpr uint32_t COUNT_XOR_MASK = 0x38757497;
    constexpr uint64_t ARRAY_DECRYPT_KEY = 0x9ED09BD7;
    constexpr uint32_t ITEM_XOR_MASK = 0xCC9C7797;
    
    constexpr uint8_t ROTATION_AMOUNT = 50;
    constexpr uint32_t CHUNK_SIZE_BITS = 16;
    constexpr uint32_t CHUNK_INDEX_MASK = 0xFFFF;
    constexpr uint32_t ITEM_SIZE_BYTES = 24;
    constexpr uint64_t UPPER_BITS_MASK = 0x3FFF00000000LL;
    constexpr uint8_t POINTER_ALIGNMENT = 8;

    uint32_t GetObjectCount()
    {
        if (!Kernel::state.process_base)
            return 0;

        const uint32_t encrypted = Memory::Read<uint32_t>(
            Kernel::state.process_base + GOBJECTS_COUNT_RVA
        );
        
        return encrypted ^ COUNT_XOR_MASK;
    }

    uintptr_t GetGObjectsChunkTable()
    {
        if (!Kernel::state.process_base)
            return 0;

        const uint64_t encrypted = Memory::Read<uint64_t>(
            Kernel::state.process_base + GOBJECTS_PTR_RVA
        );
        
        return ~__ROL8__(encrypted ^ ARRAY_DECRYPT_KEY, ROTATION_AMOUNT);
    }

    uint64_t GetObjectByIndex(uint32_t index)
    {
        if (!Kernel::state.process_base || index >= GetObjectCount())
            return 0;

        const uint64_t encrypted = Memory::Read<uint64_t>(
            Kernel::state.process_base + GOBJECTS_PTR_RVA
        );
        
        const uintptr_t chunk_table = ~__ROL8__(encrypted ^ ARRAY_DECRYPT_KEY, ROTATION_AMOUNT);
        const int32_t chunk_idx = index >> CHUNK_SIZE_BITS;
        const uintptr_t chunk_ptr = Memory::Read<uintptr_t>(
            chunk_table + (chunk_idx * sizeof(uintptr_t))
        );

        if (!chunk_ptr)
            return 0;

        const uint32_t local_index = index & CHUNK_INDEX_MASK;
        const uintptr_t item_ptr = chunk_ptr + (local_index * ITEM_SIZE_BYTES);
        
        const uint64_t raw_value = Memory::Read<uint64_t>(item_ptr);
        const uint32_t encrypted_low = Memory::Read<uint32_t>(item_ptr + 16);
        
        const uint32_t decrypted_low = encrypted_low ^ ITEM_XOR_MASK;
        const uint64_t upper_bits = raw_value & UPPER_BITS_MASK;
        const uint64_t final_value = static_cast<uint64_t>(decrypted_low) | upper_bits;
        
        return final_value * POINTER_ALIGNMENT;
    }
}