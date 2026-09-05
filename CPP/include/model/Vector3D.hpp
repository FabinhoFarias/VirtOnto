#pragma once

namespace virtonto::model {

struct Vector3D {
    float x{0.0F};
    float y{0.0F};
    float z{0.0F};

    float distanceTo(const Vector3D& other) const noexcept;
    Vector3D operator+(const Vector3D& other) const noexcept;
    Vector3D operator-(const Vector3D& other) const noexcept;
    Vector3D operator*(float scalar) const noexcept;
    Vector3D& operator+=(const Vector3D& other) noexcept;
    Vector3D& operator*=(float scalar) noexcept;
};

} // namespace virtonto::model
