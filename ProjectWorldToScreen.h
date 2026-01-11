#pragma once

inline fvector2d ProjectWorldToScreen(const fvector& world_pos)
{
    const auto& x_axis = g_Camera.transform_matrix.m[0];
    const auto& y_axis = g_Camera.transform_matrix.m[1];
    const auto& z_axis = g_Camera.transform_matrix.m[2];

    const auto offset = world_pos - g_Camera.cam_position;

    const auto proj_x = offset.dot(fvector(y_axis[0], y_axis[1], y_axis[2]));
    const auto proj_y = offset.dot(fvector(z_axis[0], z_axis[1], z_axis[2]));
    const auto proj_z = max(offset.dot(fvector(x_axis[0], x_axis[1], x_axis[2])), 1.0f);

    const float scale_factor = monitor.height_center / g_Camera.inverse_fov;
    const auto screen_x = monitor.width_center + proj_x * scale_factor / proj_z;
    const auto screen_y = monitor.height_center - proj_y * scale_factor / proj_z;

    return fvector2d(screen_x, screen_y);
}

inline bool IsPointOnScreen(const fvector2d& screen_pos)
{
    return (screen_pos.x > 0 && screen_pos.x < monitor.width &&
            screen_pos.y > 0 && screen_pos.y < monitor.height);
}