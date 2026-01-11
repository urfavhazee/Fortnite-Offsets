#pragma once
#include <algorithm>

namespace math
{
    inline fvector2d WorldToScreen(const fvector& world)
    {
        const auto& m = Camera.transform_matrix.m;
        const fvector delta = world - Camera.cam_position;

        const float x = delta.dot({ m[1][0], m[1][1], m[1][2] });
        const float y = delta.dot({ m[2][0], m[2][1], m[2][2] });
        const float z = max(delta.dot({ m[0][0], m[0][1], m[0][2] }), 1.0f);

        const float scale = height_center / Camera.inverse_fov;

        return { width_center  + (x * scale / z), height_center - (y * scale / z) };
    }

    inline bool OnScreen(const fvector2d& p)
    {
        return p.x > 0.f && p.x < width && p.y > 0.f && p.y < height;
    }
}
