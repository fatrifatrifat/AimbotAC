#pragma once

#include <cmath>
#include <numbers>

struct Vec3D
{
	float x, y, z;

	Vec3D operator+(Vec3D other)
	{
		return { this->x + other.x, this->y + other.y, this->z + other.z };
	}

	Vec3D operator-(Vec3D other)
	{
		return { this->x - other.x, this->y - other.y, this->z - other.z };
	}

	Vec3D relativeAngle()
	{
		return{
			std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
			std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
			0.0f
		};
	}
};