#include "CustomMath.h"
#include <glm/gtx/norm.hpp>

const FVector2 FVector2::Zero = FVector2(0.f, 0.f);
const FVector2 FVector2::One = FVector2(1.f, 1.f);
const FVector2 FVector2::UnitX = FVector2(1.f, 0.f);
const FVector2 FVector2::UnitY = FVector2(0.f, 1.f);

FVector2 FVector2::operator+(const FVector2& rhs) const { return FVector2(v + rhs.v); }
FVector2 FVector2::operator-(const FVector2& rhs) const { return FVector2(v - rhs.v); }
FVector2 FVector2::operator*(float s) const { return FVector2(v * s); }
FVector2 FVector2::operator/(float s) const { return FVector2(v / s); }
FVector2 FVector2::operator*(const FVector2& rhs) const { return FVector2(v * rhs.v); }
FVector2 FVector2::operator/(const FVector2& rhs) const { return FVector2(v / rhs.v); }
FVector2 FVector2::operator-() const { return FVector2(-v); }

FVector2& FVector2::operator+=(const FVector2& rhs) { v += rhs.v; return *this; }
FVector2& FVector2::operator-=(const FVector2& rhs) { v -= rhs.v; return *this; }
FVector2& FVector2::operator*=(float s) { v *= s; return *this; }
FVector2& FVector2::operator/=(float s) { v /= s; return *this; }
FVector2& FVector2::operator*=(const FVector2& rhs) { v *= rhs.v; return *this; }
FVector2& FVector2::operator/=(const FVector2& rhs) { v /= rhs.v; return *this; }

bool FVector2::operator==(const FVector2& rhs) const { return glm::all(glm::equal(v, rhs.v, glm::epsilon<float>())); }
bool FVector2::operator!=(const FVector2& rhs) const { return !(*this == rhs); }

float FVector2::Length() const { return glm::length(v); }
float FVector2::LengthSquared() const { return glm::length2(v); }
void FVector2::Normalize() { v = glm::normalize(v); }
float FVector2::Dot(const FVector2& rhs) const { return glm::dot(v, rhs.v); }
float FVector2::Cross(const FVector2& rhs) const { return v.x * rhs.v.y - v.y * rhs.v.x; }
float FVector2::Distance(const FVector2& rhs) const { return glm::distance(v, rhs.v); }
float FVector2::DistanceSquared(const FVector2& rhs) const { return glm::distance2(v, rhs.v); }
bool FVector2::IsZero(float tolerance) const { return glm::all(glm::epsilonEqual(v, glm::vec2(0.0f), tolerance)); }
void FVector2::Set(float fx, float fy) { v.x = fx; v.y = fy; }

/*
----------------------------------------
Vector2
----------------------------------------
Vector3
----------------------------------------
*/

const FVector3 FVector3::Zero = FVector3(0.f, 0.f, 0.f);
const FVector3 FVector3::One = FVector3(1.f, 1.f, 1.f);
const FVector3 FVector3::UnitX = FVector3(1.f, 0.f, 0.f);
const FVector3 FVector3::UnitY = FVector3(0.f, 1.f, 0.f);
const FVector3 FVector3::UnitZ = FVector3(0.f, 0.f, 1.f);

// Unreal Engine ÁÂÇ¥°è (X+: Forward, Y+: Right, Z+: Up)
const FVector3 FVector3::Forward = FVector3(1.0f, 0.0f, 0.0f);   // X+
const FVector3 FVector3::Backward = FVector3(-1.0f, 0.0f, 0.0f);  // X-
const FVector3 FVector3::Right = FVector3(0.0f, 1.0f, 0.0f);   // Y+
const FVector3 FVector3::Left = FVector3(0.0f, -1.0f, 0.0f);  // Y-
const FVector3 FVector3::Up = FVector3(0.0f, 0.0f, 1.0f);   // Z+
const FVector3 FVector3::Down = FVector3(0.0f, 0.0f, -1.0f);  // Z-

FVector3 FVector3::operator+(const FVector3& rhs) const { return FVector3(v + rhs.v); }
FVector3 FVector3::operator-(const FVector3& rhs) const { return FVector3(v - rhs.v); }
FVector3 FVector3::operator*(float s) const { return FVector3(v * s); }
FVector3 FVector3::operator/(float s) const { return FVector3(v / s); }
FVector3 FVector3::operator*(const FVector3& rhs) const { return FVector3(v * rhs.v); }
FVector3 FVector3::operator/(const FVector3& rhs) const { return FVector3(v / rhs.v); }
FVector3 FVector3::operator-() const { return FVector3(-v); }

FVector3& FVector3::operator+=(const FVector3& rhs) { v += rhs.v; return *this; }
FVector3& FVector3::operator-=(const FVector3& rhs) { v -= rhs.v; return *this; }
FVector3& FVector3::operator*=(float s) { v *= s; return *this; }
FVector3& FVector3::operator/=(float s) { v /= s; return *this; }
FVector3& FVector3::operator*=(const FVector3& rhs) { v *= rhs.v; return *this; }
FVector3& FVector3::operator/=(const FVector3& rhs) { v /= rhs.v; return *this; }

bool FVector3::operator==(const FVector3& rhs) const { return glm::all(glm::equal(v, rhs.v, glm::epsilon<float>())); }
bool FVector3::operator!=(const FVector3& rhs) const { return !(*this == rhs); }

float FVector3::Length() const { return glm::length(v); }
float FVector3::LengthSquared() const { return glm::length2(v); }
void FVector3::Normalize() { v = glm::normalize(v); }
float FVector3::Dot(const FVector3& rhs) const { return glm::dot(v, rhs.v); }
FVector3 FVector3::Cross(const FVector3& rhs) const { return FVector3(glm::cross(v, rhs.v)); }
float FVector3::Distance(const FVector3& rhs) const { return glm::distance(v, rhs.v); }
float FVector3::DistanceSquared(const FVector3& rhs) const { return glm::distance2(v, rhs.v); }
bool FVector3::IsZero(float tolerance) const { return glm::all(glm::epsilonEqual(v, glm::vec3(0.0f), tolerance)); }
void FVector3::Set(float fx, float fy, float fz) { v.x = fx; v.y = fy; v.z = fz; }


/*
----------------------------------------
Vector3
----------------------------------------
Vector4
----------------------------------------
*/

const FVector4 FVector4::Zero = FVector4(0.0f, 0.0f, 0.0f, 0.0f);
const FVector4 FVector4::One = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
const FVector4 FVector4::UnitX = FVector4(1.0f, 0.0f, 0.0f, 0.0f);
const FVector4 FVector4::UnitY = FVector4(0.0f, 1.0f, 0.0f, 0.0f);
const FVector4 FVector4::UnitZ = FVector4(0.0f, 0.0f, 1.0f, 0.0f);
const FVector4 FVector4::UnitW = FVector4(0.0f, 0.0f, 0.0f, 1.0f);

FVector4 FVector4::operator+(const FVector4& rhs) const { return FVector4(v + rhs.v); }
FVector4 FVector4::operator-(const FVector4& rhs) const { return FVector4(v - rhs.v); }
FVector4 FVector4::operator*(float s) const { return FVector4(v * s); }
FVector4 FVector4::operator/(float s) const { return FVector4(v / s); }
FVector4 FVector4::operator*(const FVector4& rhs) const { return FVector4(v * rhs.v); }
FVector4 FVector4::operator/(const FVector4& rhs) const { return FVector4(v / rhs.v); }
FVector4 FVector4::operator-() const { return FVector4(-v); }

FVector4& FVector4::operator+=(const FVector4& rhs) { v += rhs.v; return *this; }
FVector4& FVector4::operator-=(const FVector4& rhs) { v -= rhs.v; return *this; }
FVector4& FVector4::operator*=(float s) { v *= s; return *this; }
FVector4& FVector4::operator/=(float s) { v /= s; return *this; }
FVector4& FVector4::operator*=(const FVector4& rhs) { v *= rhs.v; return *this; }
FVector4& FVector4::operator/=(const FVector4& rhs) { v /= rhs.v; return *this; }

bool FVector4::operator==(const FVector4& rhs) const { return glm::all(glm::equal(v, rhs.v, glm::epsilon<float>())); }
bool FVector4::operator!=(const FVector4& rhs) const { return !(*this == rhs); }

float FVector4::Length() const { return glm::length(v); }
float FVector4::LengthSquared() const { return glm::length2(v); }
void FVector4::Normalize() { v = glm::normalize(v); }
FVector4 FVector4::Normalized() const { return FVector4(glm::normalize(v)); }
float FVector4::Dot(const FVector4& rhs) const { return glm::dot(v, rhs.v); }
float FVector4::Distance(const FVector4& rhs) const { return glm::distance(v, rhs.v); }
float FVector4::DistanceSquared(const FVector4& rhs) const { return glm::distance2(v, rhs.v); }
bool FVector4::IsZero(float tolerance) const { return glm::all(glm::epsilonEqual(v, glm::vec4(0.0f), tolerance)); }
void FVector4::Set(float fx, float fy, float fz, float fw) { v.x = fx; v.y = fy; v.z = fz; v.w = fw; }

/*
----------------------------------------
Vector4
----------------------------------------
Matrix
----------------------------------------
*/

const FMatrix4x4 FMatrix4x4::Identity = FMatrix4x4(1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1);
const FMatrix4x4 FMatrix4x4::Zero = FMatrix4x4(0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0);

FMatrix4x4 FMatrix4x4::operator*(const FMatrix4x4& rhs) const { return FMatrix4x4(m * rhs.m); }
FMatrix4x4& FMatrix4x4::operator*=(const FMatrix4x4& rhs) { m *= rhs.m; return *this; }

void FMatrix4x4::Transpose() { m = glm::transpose(m); }
FMatrix4x4 FMatrix4x4::Transposed() const { return FMatrix4x4(glm::transpose(m)); }
float FMatrix4x4::Determinant() const { return glm::determinant(m); }
FMatrix4x4 FMatrix4x4::Inverse() const { return FMatrix4x4(glm::inverse(m)); }
void FMatrix4x4::SetIdentity() { m = glm::mat4(1.0f); }

FMatrix4x4 FMatrix4x4::CreateTranslation(float x, float y, float z) { return FMatrix4x4(glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z))); }
FMatrix4x4 FMatrix4x4::CreateScale(float sx, float sy, float sz) { return FMatrix4x4(glm::scale(glm::mat4(1.0f), glm::vec3(sx, sy, sz))); }
FMatrix4x4 FMatrix4x4::CreateRotationX(float radians) { return FMatrix4x4(glm::rotate(glm::mat4(1.0f), radians, glm::vec3(1, 0, 0))); }
FMatrix4x4 FMatrix4x4::CreateRotationY(float radians) { return FMatrix4x4(glm::rotate(glm::mat4(1.0f), radians, glm::vec3(0, 1, 0))); }
FMatrix4x4 FMatrix4x4::CreateRotationZ(float radians) { return FMatrix4x4(glm::rotate(glm::mat4(1.0f), radians, glm::vec3(0, 0, 1))); }
FMatrix4x4 FMatrix4x4::CreateFromQuaternion(float x, float y, float z, float w) { return FMatrix4x4(glm::toMat4(glm::quat(w, x, y, z))); }
FMatrix4x4 FMatrix4x4::CreateLookAt(float eyeX, float eyeY, float eyeZ, float atX, float atY, float atZ, float upX, float upY, float upZ) {
    return FMatrix4x4(glm::lookAt(glm::vec3(eyeX, eyeY, eyeZ), glm::vec3(atX, atY, atZ), glm::vec3(upX, upY, upZ)));
}
FMatrix4x4 FMatrix4x4::CreatePerspectiveFieldOfView(float fovY, float aspect, float zn, float zf) {
    return FMatrix4x4(glm::perspective(fovY, aspect, zn, zf));
}
FMatrix4x4 FMatrix4x4::CreateOrthographic(float width, float height, float zn, float zf) {
    return FMatrix4x4(glm::ortho(-width * 0.5f, width * 0.5f, -height * 0.5f, height * 0.5f, zn, zf));
}

/*
----------------------------------------
Matrix
----------------------------------------
Quaternion
----------------------------------------
*/

FQuaternion FQuaternion::operator*(const FQuaternion& rhs) const {
    glm::quat q1 = this->ToGlm();
    glm::quat q2 = rhs.ToGlm();
    glm::quat r = q1 * q2;
    return FQuaternion(r.x, r.y, r.z, r.w);
}

FQuaternion& FQuaternion::operator*=(const FQuaternion& rhs) {
    *this = *this * rhs;
    return *this;
}

FQuaternion FQuaternion::Conjugate() const {
    return FQuaternion(-x, -y, -z, w);
}

FQuaternion FQuaternion::Inverse() const {
    glm::quat q = this->ToGlm();
    glm::quat inv = glm::inverse(q);
    return FQuaternion(inv.x, inv.y, inv.z, inv.w);
}

float FQuaternion::Length() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

void FQuaternion::Normalize() {
    float len = Length();
    if (len > 1e-8f) { x /= len; y /= len; z /= len; w /= len; }
}

FQuaternion FQuaternion::Normalized() const {
    float len = Length();
    if (len > 1e-8f) { return FQuaternion(x / len, y / len, z / len, w / len); }
    return FQuaternion(0, 0, 0, 1);
}

glm::mat4 FQuaternion::ToMatrix() const {
    return glm::toMat4(this->ToGlm());
}
