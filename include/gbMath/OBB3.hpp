#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_OBB3_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_OBB3_HPP

/** @file
*
* @brief 3D Oriented bounding box.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <gbMath/Common.hpp>
#include <gbMath/Matrix3.hpp>
#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/Vector3.hpp>

#include <algorithm>
#include <cmath>
#include <limits>
#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class OBB3 {
public:
    Point3<T> center;
    Matrix3<T> orientation;
    Vector3<T> halfwidth;

    constexpr OBB3() = default;
    constexpr explicit OBB3(DoNotInitialize_Tag)
        :center(doNotInitialize), orientation(doNotInitialize), halfwidth(doNotInitialize)
    {}
    constexpr OBB3(OBB3 const&) = default;
    constexpr OBB3& operator=(OBB3 const&) = default;

    constexpr OBB3(Point3<T> const& n_center, Matrix3<T> const& n_orientation, Vector3<T> const& n_halfwidth)
        :center(n_center), orientation(n_orientation), halfwidth(n_halfwidth)
    {}
};

template<typename T>
[[nodiscard]] constexpr inline bool intersects(OBB3<T> const& o1, OBB3<T> const& o2, T epsilon = traits::Constants<T>::Zero())
{
    // compute the rotation matrix expressing o2's axes in o1's coordinate frame
    Matrix3<T> const r_ba(
        dot(o1.orientation.row(0), o2.orientation.row(0)),
        dot(o1.orientation.row(0), o2.orientation.row(1)),
        dot(o1.orientation.row(0), o2.orientation.row(2)),
        dot(o1.orientation.row(1), o2.orientation.row(0)),
        dot(o1.orientation.row(1), o2.orientation.row(1)),
        dot(o1.orientation.row(1), o2.orientation.row(2)),
        dot(o1.orientation.row(2), o2.orientation.row(0)),
        dot(o1.orientation.row(2), o2.orientation.row(1)),
        dot(o1.orientation.row(2), o2.orientation.row(2))
    );
    // translation vector, expressed in o1's coordinate frame
    Vector3<T> const t = o1.orientation * Vector3<T>(o2.center - o1.center);

    // compute common subexpressions
    Matrix3<T> const abs_r(std::abs(r_ba.m11) + epsilon, std::abs(r_ba.m12) + epsilon, std::abs(r_ba.m13) + epsilon,
                           std::abs(r_ba.m21) + epsilon, std::abs(r_ba.m22) + epsilon, std::abs(r_ba.m23) + epsilon,
                           std::abs(r_ba.m31) + epsilon, std::abs(r_ba.m32) + epsilon, std::abs(r_ba.m33) + epsilon);

    // test axes L=A0, L=A1, L=A2
    for(int i=0; i<3; ++i) {
        T const ra = o1.halfwidth[i];
        T const rb = o2.halfwidth.x * abs_r.row(i).x +
                     o2.halfwidth.y * abs_r.row(i).y +
                     o2.halfwidth.z * abs_r.row(i).z;
        if(std::abs(t[i]) > ra + rb) { return false; }
    }

    // test axes L=B0, L=B1, L=B2
    for(int i=0; i<3; ++i) {
        T const ra = o1.halfwidth.x * abs_r.row(0)[i] +
                     o1.halfwidth.y * abs_r.row(1)[i] +
                     o1.halfwidth.z * abs_r.row(2)[i];
        T const rb = o2.halfwidth[i];
        if(std::abs(t.x*r_ba.row(0)[i] + t.y*r_ba.row(1)[i] + t.z*r_ba.row(2)[i]) > ra + rb) { return false; }
    }

    // test axis L=A0xB0
    {
        T const ra = o1.halfwidth.y * abs_r.m31 + o1.halfwidth.z * abs_r.m21;
        T const rb = o2.halfwidth.y * abs_r.m13 + o2.halfwidth.z * abs_r.m12;
        if(std::abs(t.z * r_ba.m21 - t.y * r_ba.m31) > ra + rb) { return false; }
    }

    // test axis L=A0xB1
    {
        T const ra = o1.halfwidth.y * abs_r.m32 + o1.halfwidth.z * abs_r.m22;
        T const rb = o2.halfwidth.x * abs_r.m13 + o2.halfwidth.z * abs_r.m11;
        if(std::abs(t.z * r_ba.m22 - t.y * r_ba.m32) > ra + rb) { return false; }
    }

    // test axis L=A0xB2
    {
        T const ra = o1.halfwidth.y * abs_r.m33 + o1.halfwidth.z * abs_r.m23;
        T const rb = o2.halfwidth.x * abs_r.m12 + o2.halfwidth.y * abs_r.m11;
        if(std::abs(t.z * r_ba.m23 - t.y * r_ba.m33) > ra + rb) { return false; }
    }

    // test axis L=A1xB0
    {
        T const ra = o1.halfwidth.x * abs_r.m31 + o1.halfwidth.z * abs_r.m11;
        T const rb = o2.halfwidth.y * abs_r.m23 + o2.halfwidth.z * abs_r.m22;
        if(std::abs(t.x * r_ba.m31 - t.z * r_ba.m11) > ra + rb) { return false; }
    }

    // test axis L=A1xB1
    {
        T const ra = o1.halfwidth.x * abs_r.m32 + o1.halfwidth.z * abs_r.m12;
        T const rb = o2.halfwidth.x * abs_r.m23 + o2.halfwidth.z * abs_r.m21;
        if(std::abs(t.x * r_ba.m32 - t.z * r_ba.m12) > ra + rb) { return false; }
    }

    // test axis L=A1xB2
    {
        T const ra = o1.halfwidth.x * abs_r.m33 + o1.halfwidth.z * abs_r.m13;
        T const rb = o2.halfwidth.x * abs_r.m22 + o2.halfwidth.y * abs_r.m21;
        if(std::abs(t.x * r_ba.m33 - t.z * r_ba.m13) > ra + rb) { return false; }
    }

    // test axis L=A2xB0
    {
        T const ra = o1.halfwidth.x * abs_r.m21 + o1.halfwidth.y * abs_r.m11;
        T const rb = o2.halfwidth.y * abs_r.m33 + o2.halfwidth.z * abs_r.m32;
        if(std::abs(t.y * r_ba.m11 - t.x * r_ba.m21) > ra + rb) { return false; }
    }

    // test axis L=A2xB1
    {
        T const ra = o1.halfwidth.x * abs_r.m22 + o1.halfwidth.y * abs_r.m12;
        T const rb = o2.halfwidth.x * abs_r.m33 + o2.halfwidth.z * abs_r.m31;
        if(std::abs(t.y * r_ba.m12 - t.x * r_ba.m22) > ra + rb) { return false; }
    }

    // test axis L=A2xB2
    {
        T const ra = o1.halfwidth.x * abs_r.m23 + o1.halfwidth.y * abs_r.m13;
        T const rb = o2.halfwidth.x * abs_r.m32 + o2.halfwidth.z * abs_r.m31;
        if(std::abs(t.y * r_ba.m13 - t.x * r_ba.m23) > ra + rb) { return false; }
    }

    return true;
}
}
#endif
