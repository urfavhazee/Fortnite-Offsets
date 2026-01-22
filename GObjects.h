    uint32_t get_object_count()
    {
        if (cached_count) return cached_count;
        if (!hv::state.process_base) return 0;
        const uint32_t encrypted_count = hv::read<uint32_t>((hv::state.process_base + Config->gobjects_count_rva));
        cached_count = __ROL4__(encrypted_count ^ 0x75DB1A01, 18);
        return cached_count;
    }
 
    uint64_t get_object_by_index(uint32_t index)
    {
        if (!hv::state.process_base) return 0;
 
        const uintptr_t GObjectsEncryptedRVA = 0x1785AFB0;
        const uint64_t encrypted_gobjects = hv::read<uint64_t>(hv::state.process_base + GObjectsEncryptedRVA);
        const uintptr_t gObjectsChunkTable = encrypted_gobjects ^ 0xFFFFFFFFCCF54342uLL;
 
        const int32_t chunk_index = index >> 16;
        const uintptr_t chunk_address = hv::read<uintptr_t>(gObjectsChunkTable + (chunk_index * 8));
        if (!chunk_address) return 0;
        const uint32_t index_in_chunk = index & 0xFFFF;
        const uintptr_t item_address = chunk_address + (index_in_chunk * 24);
 
 
        const uint64_t item_raw_value = hv::read<uint64_t>(item_address);
        const uint32_t encrypted_lower_part = hv::read<uint32_t>(item_address + 8);
 
        const uint32_t lower_decrypted = __ROL4__(encrypted_lower_part ^ 0x6BC5CA79, 18);
 
        const uint64_t upper_part = item_raw_value & 0x3FFF00000000LL;
        const uint64_t reconstructed_value = (uint64_t)lower_decrypted | upper_part;
 
        return reconstructed_value * 8;
    }
