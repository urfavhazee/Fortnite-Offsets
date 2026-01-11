// camera.h
#pragma once

class Camera
{
private:
    static constexpr uintptr_t VIEW_MATRIX_OFFSET = 0xd0;
    static constexpr uintptr_t VIEW_STATE_OFFSET = 0x8;
    static constexpr uintptr_t PROJECTION_OFFSET = 0x940;
    static constexpr uintptr_t FOV_OFFSET = 0x740;
    
    static constexpr float DEGREES_PER_RADIAN = 180.0f / PI;
    static constexpr float RAD_TO_DEG = 180.0f / M_PI;

    uintptr_t view_state_ptr = 0;

public:
    fvector cam_position{};
    frotator cam_rotation{};
    float field_of_view = 0.0f;
    D3DMATRIX transform_matrix;
    float inverse_fov;

    inline void InitializeViewState()
    {
        const uintptr_t view_matrix_addr = Memory::Read<uintptr_t>(Cached.LocalPlayer + VIEW_MATRIX_OFFSET);
        view_state_ptr = Memory::Read<uintptr_t>(view_matrix_addr + VIEW_STATE_OFFSET);
    }

    inline void UpdateCameraData()
    {
        if (!view_state_ptr)
        {
            InitializeViewState();
        }

        const auto projection_matrix = Memory::Read<fmatrix>(view_state_ptr + PROJECTION_OFFSET);

        cam_rotation.pitch = asin(projection_matrix.z_plane.w) * DEGREES_PER_RADIAN;
        cam_rotation.yaw = atan2(projection_matrix.y_plane.w, projection_matrix.x_plane.w) * DEGREES_PER_RADIAN;
        cam_rotation.roll = 0.0f;

        cam_position.x = projection_matrix.m[3][0];
        cam_position.y = projection_matrix.m[3][1];
        cam_position.z = projection_matrix.m[3][2];

        const float fov_radians = atanf(1.0f / Memory::Read<double>(view_state_ptr + FOV_OFFSET)) * 2.0f;
        field_of_view = fov_radians * RAD_TO_DEG;
    }
};

Camera g_Camera;