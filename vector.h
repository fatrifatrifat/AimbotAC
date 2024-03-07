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

	Vec3D relativeAngle(Vec3D other)
	{
		float dx = other.x - this->x;
		float dy = other.y - this->y;
		float dz = other.z - this->z;

		float yaw = std::atan2(dy, dx) * (180.0f / std::numbers::pi);

		float pitch = std::atan2(dz, std::sqrt(dx * dx + dy * dy)) * (180.0f / std::numbers::pi);

		if (yaw < 0)
			yaw += 360.0f;

		return { yaw+90, pitch, 0.0f };
	}


	float distanceCalculate(Vec3D other)
	{
		float distance;
		distance = std::sqrt(pow((other.x - this->x), 2) + pow((other.y - this->y), 2) + pow((other.z - this->z), 2));
		return distance;
	}
};