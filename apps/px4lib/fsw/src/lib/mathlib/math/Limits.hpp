#pragma once

namespace math
{

template<typename _Tp>
inline constexpr const _Tp &min(const _Tp &a, const _Tp &b)
{
    return (a < b) ? a : b;
}

template<typename _Tp>
inline constexpr const _Tp &max(const _Tp &a, const _Tp &b)
{
    return (a > b) ? a : b;
}

template<typename _Tp>
inline constexpr const _Tp &constrain(const _Tp &val, const _Tp &min_val, const _Tp &max_val)
{
    return (val < min_val) ? min_val : ((val > max_val) ? max_val : val);
}

float radians(float degrees);

double radians(double degrees);

float degrees(float radians);

double degrees(double radians);

}
