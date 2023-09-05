#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_MATRIX_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_MATRIX_HPP

/** @file
 *
 * @brief MxN Matrix.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>

#include <gbMath/Common.hpp>
#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/MatrixPolicies.hpp>
#include <gbMath/Vector.hpp>

#include <array>
#include <algorithm>
#include <cmath>
#include <concepts>
#include <numeric>
#include <utility>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T, std::size_t M, std::size_t N>
class Matrix
{
public:
    using ValueType = T;
    static_assert(M > 0, "Matrix must have at least one row");
    static_assert(N > 0, "Matrix must have at least one column");

    std::array<T, M*N> m;

    constexpr Matrix()
        :m{}
    {}

    constexpr Matrix(DoNotInitialize_Tag)
    {}

    template<typename... Args>
    constexpr explicit Matrix(Args... args)
        requires((sizeof...(args) == M*N) && (std::same_as<Args, T> && ...))
    : m{args...}
    {}

    constexpr Matrix(Matrix const&) = default;
    constexpr Matrix& operator=(Matrix const&) = default;

    template<std::convertible_to<T> U>
    constexpr explicit Matrix(Matrix<U, M, N> const& other)
    {
        std::transform(begin(other.m), end(other.m), begin(m),
            [](U const& u) -> T { return static_cast<T>(u); });
    }

    constexpr explicit Matrix(T const* arr, MatrixPolicies::InputOrder_RowMajor)
    {
        std::copy(arr, arr + M * N, begin(m));
    }

    constexpr explicit Matrix(T const* arr, MatrixPolicies::InputOrder_ColumnMajor)
    {
        for (std::size_t j = 0; j < N; ++j) {
            for (std::size_t i = 0; i < M; ++i) {
                m[i * N + j] = arr[j * M + i];
            }
        }
    }

    [[nodiscard]] constexpr std::pair<std::size_t, std::size_t> dimension() const
    {
        return std::make_pair(M, N);
    }

    [[nodiscard]] constexpr bool is_square() const
    {
        return M == N;
    }

    [[nodiscard]] constexpr T& operator[](std::size_t idx)
    {
        return m[idx];
    }

    [[nodiscard]] constexpr T const& operator[](std::size_t idx) const
    {
        return m[idx];
    }

    [[nodiscard]] constexpr T& operator()(std::size_t r, std::size_t c)
    {
        return m[r * N + c];
    }

    [[nodiscard]] constexpr T const& operator()(std::size_t r, std::size_t c) const
    {
        return m[r * N + c];
    }

    [[nodiscard]] constexpr Vector<T, N> row(std::size_t idx) const
    {
        Vector<T, N> ret(doNotInitialize);
        for (std::size_t j = 0; j < N; ++j) {
            ret[j] = m[idx * N + j];
        }
        return ret;
    }

    [[nodiscard]] constexpr Vector<T, M> column(std::size_t idx) const
    {
        Vector<T, M> ret(doNotInitialize);
        for (std::size_t j = 0; j < M; ++j) {
            ret[j] = m[j * N + idx];
        }
        return ret;
    }

    constexpr void swap_rows(std::size_t r1, std::size_t r2)
    {
        using std::swap;
        if (r1 == r2) { return; }
        for (std::size_t i = 0; i < N; ++i) {
            swap((*this)(r1, i), (*this)(r2, i));
        }
    }

    constexpr void swap_columns(std::size_t c1, std::size_t c2)
    {
        using std::swap;
        if (c1 == c2) { return; }
        for (std::size_t i = 0; i < M; ++i) {
            swap((*this)(i, c1), (*this)(i, c2));
        }
    }

    constexpr Matrix& operator+=(Matrix const& rhs)
    {
        std::transform(begin(m), end(m), begin(rhs.m), begin(m), std::plus<T>{});
        return *this;
    }

    constexpr Matrix& operator-=(Matrix const& rhs)
    {
        std::transform(begin(m), end(m), begin(rhs.m), begin(m), std::minus<T>{});
        return *this;
    }

    constexpr Matrix& operator*=(T f)
    {
        std::transform(begin(m), end(m), begin(m), [f](T n) { return n * f; });
        return *this;
    }

    constexpr Matrix& operator/=(T f)
    {
        std::transform(begin(m), end(m), begin(m), [f](T n) { return n / f; });
        return *this;

    }

    constexpr Matrix& operator*=(Matrix const& rhs) requires(M == N)
    {
        *this = (*this) * rhs;
        return *this;
    }

#ifndef __clang__
    [[nodiscard]] friend constexpr auto operator<=>(Matrix const&, Matrix const&) = default;
#else
    // clang currently fails to generate comparison operators correctly.
    [[nodiscard]] friend constexpr auto operator==(Matrix const& lhs, Matrix const& rhs)
    {
        return lhs.m == rhs.m;
    }

    [[nodiscard]] friend constexpr auto operator!=(Matrix const& lhs, Matrix const& rhs)
    {
        return !(lhs == rhs);
    }

    [[nodiscard]] friend constexpr auto operator<(Matrix const& lhs, Matrix const& rhs)
    {
        return lhs.m < rhs.m;
    }

    [[nodiscard]] friend constexpr auto operator<=(Matrix const& lhs, Matrix const& rhs)
    {
        return (lhs < rhs) || (lhs == rhs);
    }

    [[nodiscard]] friend constexpr auto operator>(Matrix const& lhs, Matrix const& rhs)
    {
        return (rhs < lhs);
    }

    [[nodiscard]] friend constexpr auto operator>=(Matrix const& lhs, Matrix const& rhs)
    {
        return (rhs <= lhs);
    }
#endif

    [[nodiscard]] friend constexpr Matrix operator+(Matrix const& lhs, Matrix const& rhs)
    {
        Matrix ret(doNotInitialize);
        std::transform(begin(lhs.m), end(lhs.m), begin(rhs.m), begin(ret.m), std::plus<T>{});
        return ret;
    }

    [[nodiscard]] friend constexpr Matrix operator-(Matrix const& lhs, Matrix const& rhs)
    {
        Matrix ret(doNotInitialize);
        std::transform(begin(lhs.m), end(lhs.m), begin(rhs.m), begin(ret.m), std::minus<T>{});
        return ret;
    }

    [[nodiscard]] friend constexpr Matrix operator*(Matrix const& lhs, T f)
    {
        Matrix ret(doNotInitialize);
        std::transform(begin(lhs.m), end(lhs.m), begin(ret.m), [f](T n) { return n * f; });
        return ret;
    }

    [[nodiscard]] friend constexpr Matrix operator*(T f, Matrix const& rhs)
    {
        Matrix ret(doNotInitialize);
        std::transform(begin(rhs.m), end(rhs.m), begin(ret.m), [f](T n) { return f * n; });
        return ret;
    }

    [[nodiscard]] friend constexpr Matrix operator/(Matrix const& lhs, T f)
    {
        Matrix ret(doNotInitialize);
        std::transform(begin(lhs.m), end(lhs.m), begin(ret.m), [f](T n) { return n / f; });
        return ret;
    }

    template<std::size_t Q>
    [[nodiscard]] friend constexpr Matrix<T, M, Q> operator*(Matrix<T, M, N> const& lhs, Matrix<T, N, Q>  const& rhs)
    {
        Matrix<T, M, Q> ret(doNotInitialize);
        for (std::size_t i = 0; i < M; ++i) {
            for (std::size_t j = 0; j < Q; ++j) {
                T acc = traits::Constants<T>::Zero();
                for (std::size_t k = 0; k < N; ++k) {
                    acc += lhs(i, k) * rhs(k, j);
                }
                ret(i, j) = acc;
            }
        }
        return ret;
    }

    [[nodiscard]] friend constexpr Vector<T, M> operator*(Matrix const& m, Vector<T, N> const& v)
    {
        Vector<T, M> ret(doNotInitialize);
        for (std::size_t i = 0; i < M; ++i) {
            T acc = traits::Constants<T>::Zero();
            for (std::size_t k = 0; k < N; ++k) {
                acc += m(i, k) * v[k];
            }
            ret[i] = acc;
        }
        return ret;
    }
};

template<typename T, std::size_t M, std::size_t N, typename... Args>
[[nodiscard]] constexpr inline Matrix<T, M, N> matrix_from_row_vectors(Args... args)
    requires((sizeof...(args) == M) && (std::same_as<Args, Vector<T, N>> && ...))
{
    std::array<Vector<T, N>, M> varr{ args... };
    Matrix<T, M, N> ret(doNotInitialize);
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            ret.m[i * N + j] = varr[i][j];
        }
    }
    return ret;
}

template<typename T, std::size_t M, std::size_t N, typename... Args>
[[nodiscard]] constexpr inline Matrix<T, M, N> matrix_from_column_vectors(Args... args)
    requires((sizeof...(args) == N) && (std::same_as<Args, Vector<T, M>> && ...))
{
    std::array<Vector<T, M>, N> varr{ args... };
    Matrix<T, M, N> ret(doNotInitialize);
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            ret.m[i * N + j] = varr[j][i];
        }
    }
    return ret;
}

template<typename T, std::size_t M, std::size_t N>
[[nodiscard]] constexpr inline Matrix<T, N, M> transpose(Matrix<T, M, N> const& m)
{
    Matrix<T, N, M> ret(doNotInitialize);
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            ret(j, i) = m(i, j);
        }
    }
    return ret;
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr inline Matrix<T, N, N> identityMN()
{
    using ::GHULBUS_MATH_NAMESPACE::traits::Constants;
    Matrix<T, N, N> ret(doNotInitialize);
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            ret(i, j) = (i == j) ? Constants<T>::One() : Constants<T>::Zero();
        }
    }
    return ret;
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr inline T trace(Matrix<T, N, N> const& m)
{
    T ret = traits::Constants<T>::Zero();
    for (std::size_t i = 0; i < N; ++i) {
        ret += m(i, i);
    }
    return ret;
}

template<typename T, std::size_t N>
struct LUDecomposition {
    Matrix<T, N, N> m;
    Vector<std::size_t, N> indices;
    T det_sign;

    struct Singular_T {};

    constexpr LUDecomposition()
        :m(doNotInitialize), indices(doNotInitialize)
    {}

    void mark_singular()
    {
        m = Matrix<T, N, N>{};
        indices = Vector<std::size_t, N>{};
        det_sign = traits::Constants<T>::Zero();
    }

    [[nodiscard]] constexpr explicit operator bool() {
        return det_sign != traits::Constants<T>::Zero();
    }

    [[nodiscard]] constexpr Matrix<T, N, N> getL() const {
        Matrix<T, N, N> l = identityMN<T, N>();
        for (std::size_t i = 1; i < N; ++i) {
            for (std::size_t j = 0; j < i; ++j) {
                l(i, j) = m(i, j);
            }
        }
        return l;
    }

    [[nodiscard]] constexpr Matrix<T, N, N> getU() const {
        Matrix<T, N, N> u;
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = i; j < N; ++j) {
                u(i, j) = m(i, j);
            }
        }
        return u;
    }

    [[nodiscard]] constexpr Matrix<T, N, N> getP() const {
        Matrix<T, N, N> ret(doNotInitialize);
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
                ret(i, j) = (indices[j] == i) ? traits::Constants<T>::One() : traits::Constants<T>::Zero();
            }
        }
        return ret;
    }

    [[nodiscard]] constexpr T getDeterminant() const {
        T ret = traits::Constants<T>::One();
        for (std::size_t i = 0; i < N; ++i) {
            ret *= m(i, i);
        }
        return det_sign * ret;
    }
};

template<typename T, std::size_t N>
[[nodiscard]] constexpr inline LUDecomposition<T, N> lu_decompose(Matrix<T, N, N> const& m)
{
    using std::abs;
    using std::swap;
    LUDecomposition<T, N> ret;
    Vector<T, N> row_normalizer(doNotInitialize);
    ret.det_sign = traits::Constants<T>::One();

    // take as a normalizer the max element from each row
    for (std::size_t i = 0; i < N; ++i) {
        T max_value = traits::Constants<T>::Zero();
        for (std::size_t j = 0; j < N; ++j) {
            T const v = abs(m(i, j));
            if (v > max_value) { max_value = v; }
        }
        if (max_value == traits::Constants<T>::Zero()) {
            // matrix is singular
            ret.mark_singular();
            return ret;
        }
        row_normalizer[i] =  traits::Constants<T>::One() / max_value;
        ret.indices[i] = i;
    }

    // perform decomposition (doolittle's method)
    ret.m = m;
    for (std::size_t j = 0; j < N; ++j) {
        for (std::size_t i = 1; i < j; ++i) {
            T sum = ret.m(i, j);
            for (std::size_t k = 0; k < i; ++k) {
                sum -= ret.m(i, k) * ret.m(k, j);
            }
            ret.m(i, j) = sum;
        }

        // find pivot
        std::size_t pivot_row = N;
        T max_value = traits::Constants<T>::Zero();
        for (std::size_t i = j; i < N; ++i) {
            T sum = ret.m(i, j);
            for (std::size_t k = 0; k < j; ++k) {
                sum -= ret.m(i, k) * ret.m(k, j);
            }
            ret.m(i, j) = sum;

            sum = abs(sum) * row_normalizer[i];
            if (sum > max_value) {
                max_value = sum;
                pivot_row = i;
            }
        }

        // swap rows with pivot
        if (pivot_row != j) {
            if (pivot_row == N) {
                ret.mark_singular();
                return ret;
            }
            ret.m.swap_rows(pivot_row, j);
            swap(ret.indices[pivot_row], ret.indices[j]);
            row_normalizer[pivot_row] = row_normalizer[j];
            ret.det_sign = -ret.det_sign;
        }

        // divide by pivot
        if (j != N - 1) {
            T denom = traits::Constants<T>::One() / ret.m(j, j);
            for (std::size_t i = j + 1; i < N; ++i) {
                ret.m(i, j) *= denom;
            }
        }
    }

    return ret;
}
}
#endif
