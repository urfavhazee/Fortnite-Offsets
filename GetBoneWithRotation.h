static auto GetBone(uintptr_t skeletal_mesh, int bone_index) -> fvector {
	int32_t active_transforms_count = Memory::Read<int32_t>(skeletal_mesh + 0x5f0 + 0x48);
	uintptr_t bone_array_ptr = Memory::Read<uintptr_t>(skeletal_mesh + 0x5f0 + active_transforms_count * 0x10);

	if (!bone_array_ptr) return fvector(0, 0, 0);

	ftransform bone = Memory::Read<ftransform>(bone_array_ptr + (bone_index * sizeof(ftransform)));

	ftransform component_to_world = Memory::Read<ftransform>(skeletal_mesh + offset::ComponentToWorld);

	D3DMATRIX matrix = matrix_multiplication(bone.to_matrix_with_scale(), component_to_world.to_matrix_with_scale());
	return fvector(matrix._41, matrix._42, matrix._43);
}