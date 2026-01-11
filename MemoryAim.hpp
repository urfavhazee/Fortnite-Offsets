constexpr float AIM_SCALE_FACTOR = 5.0f;
constexpr float MIN_SPEED_THRESHOLD = 1.0f;
constexpr float MAX_SMOOTHNESS_VALUE = 101.0f;

bool ApplyAimOffset(const Vector3& position_offset)
{
    Memory::Write<Vector3>(Cached.PlayerController + offsets::PlayerAimOffset, position_offset);
    return true;
}

void ProcessTargetAim(uintptr_t target_mesh, const Vector2& screen_target)
{
    Vector2 calculated_offset{};
    
    const float smoothing_value = settings::aimbot::aimbot;
    float aim_speed = MAX_SMOOTHNESS_VALUE - smoothing_value;
    
    if (aim_speed < MIN_SPEED_THRESHOLD)
        aim_speed = MIN_SPEED_THRESHOLD;

    const float center_x = static_cast<float>(Width) * 0.5f;
    const float center_y = static_cast<float>(Height) * 0.5f;

    if (screen_target.x > center_x)
    {
        calculated_offset.x = -(center_x - screen_target.x) * aim_speed;
        
        if (calculated_offset.x + center_x > Width)
            calculated_offset.x = 0;
    }
    else if (screen_target.x < center_x)
    {
        calculated_offset.x = (screen_target.x - center_x) * aim_speed;
        
        if (calculated_offset.x + center_x < 0)
            calculated_offset.x = 0;
    }

    if (screen_target.y > center_y)
    {
        calculated_offset.y = -(center_y - screen_target.y) * aim_speed;
        
        if (calculated_offset.y + center_y > Height)
            calculated_offset.y = 0;
    }
    else if (screen_target.y < center_y)
    {
        calculated_offset.y = (screen_target.y - center_y) * aim_speed;
        
        if (calculated_offset.y + center_y < 0)
            calculated_offset.y = 0;
    }

    const float normalized_y = -calculated_offset.y / AIM_SCALE_FACTOR;
    const float normalized_x = calculated_offset.x / AIM_SCALE_FACTOR;
    
    ApplyAimOffset(Vector3(normalized_y, normalized_x, 0));
}