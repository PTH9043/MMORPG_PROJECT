#pragma once


// FastMathStructs_SIMD.hpp
#pragma once

#define GLM_FORCE_INTRINSICS      // SIMD 인트린식 코드 경로 강제 활성화  
#define GLM_FORCE_SSE2            // 또는 GLM_FORCE_SSE42, GLM_FORCE_AVX2 등 사용 가능  
#define GLM_FORCE_ALIGNED_GENTYPES // 정렬된 제네릭 타입 사용  
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct FVector2 {
    union {
        glm::vec2 v;
        struct { float x, y; };
    };

    FVector2() : v(0.0f, 0.0f) {}
    explicit FVector2(float fx, float fy) : v(fx, fy) {}
    FVector2(const FVector2& rhs) : v(rhs.v) {}
    FVector2& operator=(const FVector2& rhs) { v = rhs.v; return *this; }
    explicit FVector2(const glm::vec2& vv) : v(vv) {}

    // 연산자
    FVector2 operator+(const FVector2& rhs) const;
    FVector2 operator-(const FVector2& rhs) const;
    FVector2 operator*(float s) const;
    FVector2 operator/(float s) const;
    FVector2 operator*(const FVector2& rhs) const;
    FVector2 operator/(const FVector2& rhs) const;
    FVector2 operator-() const;

    FVector2& operator+=(const FVector2& rhs);
    FVector2& operator-=(const FVector2& rhs);
    FVector2& operator*=(float s);
    FVector2& operator/=(float s);
    FVector2& operator*=(const FVector2& rhs);
    FVector2& operator/=(const FVector2& rhs);

    bool operator==(const FVector2& rhs) const;
    bool operator!=(const FVector2& rhs) const;

    float Length() const;
    float LengthSquared() const;
    void Normalize();
    float Dot(const FVector2& rhs) const;
    float Cross(const FVector2& rhs) const;
    float Distance(const FVector2& rhs) const;
    float DistanceSquared(const FVector2& rhs) const;
    bool IsZero(float tolerance = glm::epsilon<float>()) const;
    void Set(float fx, float fy);

    static const FVector2 Zero;
    static const FVector2 One;
    static const FVector2 UnitX;
    static const FVector2 UnitY;
};

/*
----------------------------------------
Vector2
----------------------------------------
Vector3
----------------------------------------
*/


struct FVector3 {
    union {
        glm::vec3 v;
        struct { float x, y, z; };
    };

    FVector3() : v(0.0f, 0.0f, 0.0f) {}
    explicit FVector3(float fx, float fy, float fz) : v(fx, fy, fz) {}
    FVector3(const FVector3& rhs) : v(rhs.v) {}
    FVector3& operator=(const FVector3& rhs) { v = rhs.v; return *this; }
    explicit FVector3(const glm::vec3& vv) : v(vv) {}

    FVector3 operator+(const FVector3& rhs) const;
    FVector3 operator-(const FVector3& rhs) const;
    FVector3 operator*(float s) const;
    FVector3 operator/(float s) const;
    FVector3 operator*(const FVector3& rhs) const;
    FVector3 operator/(const FVector3& rhs) const;
    FVector3 operator-() const;

    FVector3& operator+=(const FVector3& rhs);
    FVector3& operator-=(const FVector3& rhs);
    FVector3& operator*=(float s);
    FVector3& operator/=(float s);
    FVector3& operator*=(const FVector3& rhs);
    FVector3& operator/=(const FVector3& rhs);

    bool operator==(const FVector3& rhs) const;
    bool operator!=(const FVector3& rhs) const;

    float Length() const;
    float LengthSquared() const;
    void Normalize();
    float Dot(const FVector3& rhs) const;
    FVector3 Cross(const FVector3& rhs) const;
    float Distance(const FVector3& rhs) const;
    float DistanceSquared(const FVector3& rhs) const;
    bool IsZero(float tolerance = glm::epsilon<float>()) const;
    void Set(float fx, float fy, float fz);

    static const FVector3 Zero;
    static const FVector3 One;
    static const FVector3 UnitX;
    static const FVector3 UnitY;
    static const FVector3 UnitZ;

    // Unreal 스타일 방향 벡터
    static const FVector3 Forward; // X+ (언리얼)
    static const FVector3 Backward;// X- (언리얼)
    static const FVector3 Right;   // Y+ (언리얼)
    static const FVector3 Left;    // Y- (언리얼)
    static const FVector3 Up;      // Z+ (언리얼)
    static const FVector3 Down;    // Z- (언리얼)
};


/*
----------------------------------------
Vector3
----------------------------------------
Vector4
----------------------------------------
*/


struct FVector4 {
    union {
        glm::vec4 v;
        struct { float x, y, z, w; };
    };

    FVector4() : v(0.0f, 0.0f, 0.0f, 0.0f) {}
    explicit FVector4(float fx, float fy, float fz, float fw) : v(fx, fy, fz, fw) {}
    FVector4(const FVector4& rhs) : v(rhs.v) {}
    FVector4& operator=(const FVector4& rhs) { v = rhs.v; return *this; }
    explicit FVector4(const glm::vec4& vv) : v(vv) {}

    FVector4 operator+(const FVector4& rhs) const;
    FVector4 operator-(const FVector4& rhs) const;
    FVector4 operator*(float s) const;
    FVector4 operator/(float s) const;
    FVector4 operator*(const FVector4& rhs) const;
    FVector4 operator/(const FVector4& rhs) const;
    FVector4 operator-() const;

    FVector4& operator+=(const FVector4& rhs);
    FVector4& operator-=(const FVector4& rhs);
    FVector4& operator*=(float s);
    FVector4& operator/=(float s);
    FVector4& operator*=(const FVector4& rhs);
    FVector4& operator/=(const FVector4& rhs);

    bool operator==(const FVector4& rhs) const;
    bool operator!=(const FVector4& rhs) const;

    float Length() const;
    float LengthSquared() const;
    void Normalize();
    FVector4 Normalized() const;
    float Dot(const FVector4& rhs) const;
    float Distance(const FVector4& rhs) const;
    float DistanceSquared(const FVector4& rhs) const;
    bool IsZero(float tolerance = glm::epsilon<float>()) const;
    void Set(float fx, float fy, float fz, float fw);

    static const FVector4 Zero;
    static const FVector4 One;
    static const FVector4 UnitX;
    static const FVector4 UnitY;
    static const FVector4 UnitZ;
    static const FVector4 UnitW;
};

/*
----------------------------------------
Vector4
----------------------------------------
Matrix
----------------------------------------
*/

struct FMatrix4x4 {
    glm::mat4 m;

    FMatrix4x4() : m(1.0f) {} // glm::mat4 기본은 단위행렬
    explicit FMatrix4x4(const glm::mat4& mm) : m(mm) {}
    FMatrix4x4(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33
    ) : m(
        m00, m01, m02, m03,
        m10, m11, m12, m13,
        m20, m21, m22, m23,
        m30, m31, m32, m33
    ) {
    }
    FMatrix4x4(const FMatrix4x4& mat) : m(mat.m) {}
    FMatrix4x4& operator=(const FMatrix4x4& mat) { m = mat.m; return *this; }

    float* operator[](int i) { return &m[i][0]; }
    const float* operator[](int i) const { return &m[i][0]; }

    FMatrix4x4 operator*(const FMatrix4x4& rhs) const;
    FMatrix4x4& operator*=(const FMatrix4x4& rhs);

    void Transpose();
    FMatrix4x4 Transposed() const;
    float Determinant() const;
    FMatrix4x4 Inverse() const;
    void SetIdentity();

    static FMatrix4x4 CreateTranslation(float x, float y, float z);
    static FMatrix4x4 CreateScale(float sx, float sy, float sz);
    static FMatrix4x4 CreateRotationX(float radians);
    static FMatrix4x4 CreateRotationY(float radians);
    static FMatrix4x4 CreateRotationZ(float radians);
    static FMatrix4x4 CreateFromQuaternion(float x, float y, float z, float w);
    static FMatrix4x4 CreateLookAt(
        float eyeX, float eyeY, float eyeZ,
        float atX, float atY, float atZ,
        float upX, float upY, float upZ
    );
    static FMatrix4x4 CreatePerspectiveFieldOfView(float fovY, float aspect, float zn, float zf);
    static FMatrix4x4 CreateOrthographic(float width, float height, float zn, float zf);

    static const FMatrix4x4 Identity;
    static const FMatrix4x4 Zero;
};

/*
----------------------------------------
Matrix
----------------------------------------
Quaternion
----------------------------------------
*/

struct FQuaternion {
    float x, y, z, w; // 언리얼 FQuat과 동일 순서

    FQuaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
    FQuaternion(float fx, float fy, float fz, float fw) : x(fx), y(fy), z(fz), w(fw) {}
    FQuaternion(const FQuaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
    FQuaternion& operator=(const FQuaternion& q) { x = q.x; y = q.y; z = q.z; w = q.w; return *this; }
    explicit FQuaternion(const glm::quat& qq) : x(qq.x), y(qq.y), z(qq.z), w(qq.w) {}
    glm::quat ToGlm() const { return glm::quat(w, x, y, z); }

    FQuaternion operator*(const FQuaternion& rhs) const;
    FQuaternion& operator*=(const FQuaternion& rhs);

    FQuaternion Conjugate() const;
    FQuaternion Inverse() const;
    float Length() const;
    void Normalize();
    FQuaternion Normalized() const;
    glm::mat4 ToMatrix() const;

    static const FQuaternion Identity;
};