bool IsVisible(uintptr_t Mesh) {
	auto Seconds = Memory::Read<double>(Cached.UWorld + Offsets::CameraRotation + 0x10);
	auto LastRenderTime = Memory::Read<float>(Mesh + Offsets::LastRenderTime);
	return Seconds - LastRenderTime <= 0.06f;
}