#ifndef STRONGTYPE_HPP_INCLUDED
#define STRONGTYPE_HPP_INCLUDED
//
// strong-type.hpp
//
#include <ostream>
#include <type_traits>

namespace util
{

    // Responsible for wrapping types with a phantom tag Parameter_t to make them stronger.
    template <typename T, typename Parameter_t>
    struct StrongType
    {
        static_assert(
            (std::is_integral_v<T> && !std::is_same_v<T, bool>),
            "This class was designed for integer types only.  No biscuit.");

        constexpr StrongType() noexcept = default;

        constexpr explicit StrongType(const T & value)
            : m_value(value)
        {}

        constexpr StrongType(const StrongType &) noexcept = default;
        constexpr StrongType(StrongType &&) noexcept      = default;

        constexpr StrongType & operator=(const StrongType &) noexcept = default;
        constexpr StrongType & operator=(StrongType &&) noexcept      = default;

        constexpr T & get() noexcept { return m_value; }
        constexpr const T & get() const noexcept { return m_value; }

        template <typename FromType_t>
        constexpr static StrongType<T, Parameter_t> make(const FromType_t fromValue)
        {
            return StrongType<T, Parameter_t>(static_cast<T>(fromValue));
        }

        template <typename AsType_t>
        constexpr AsType_t as() const
        {
            return static_cast<AsType_t>(this->m_value);
        }

        constexpr const StrongType abs() const
        {
            return StrongType<T, Parameter_t>(std::abs(this->m_value));
        }

        constexpr StrongType & operator+=(const StrongType & rhs)
        {
            this->m_value += rhs.m_value;
            return *this;
        }

        constexpr StrongType & operator-=(const StrongType & rhs)
        {
            this->m_value -= rhs.m_value;
            return *this;
        }

        constexpr StrongType & operator*=(const StrongType & rhs)
        {
            this->m_value *= rhs.m_value;
            return *this;
        }

        constexpr StrongType & operator/=(const StrongType & rhs)
        {
            this->m_value /= rhs.m_value;
            return *this;
        }

        constexpr StrongType operator+(const StrongType & rhs) const
        {
            return (StrongType(*this) += rhs);
        }

        constexpr StrongType operator-(const StrongType & rhs) const
        {
            return (StrongType(*this) -= rhs);
        }

        constexpr StrongType operator*(const StrongType & rhs) const
        {
            return (StrongType(*this) *= rhs);
        }

        constexpr StrongType operator/(const StrongType & rhs) const
        {
            return (StrongType(*this) /= rhs);
        }

        constexpr StrongType & operator++()
        {
            ++(this->m_value);
            return *this;
        }

        constexpr StrongType operator++(int)
        {
            const StrongType temp{ *this };
            operator++();
            return temp;
        }

        constexpr StrongType & operator--()
        {
            --(this->m_value);
            return *this;
        }

        constexpr StrongType operator--(int)
        {
            const StrongType temp{ *this };
            operator--();
            return temp;
        }

        // template <typename I, typename U>
        // friend void to_json(json & j, const StrongType<I, U> & st);
        //
        // template <typename I, typename U>
        // friend void from_json(const json & j, StrongType<I, U> & st);

        auto operator<=>(const StrongType<T, Parameter_t> &) const = default;

      private:
        T m_value;
    };

    namespace test
    {
        struct TestTag;
        static_assert(
            std::is_trivial_v<StrongType<int, TestTag>>,
            "StrongTypes of simple numeric types like int SHOULD be trivial.  No biscuit.");
    } // namespace test

    // template <typename T, typename Parameter_t>
    // inline void to_json(json & j, const StrongType<T, Parameter_t> & st)
    //{
    //    j = json{ { "value", st.m_value } };
    //}
    //
    // template <typename T, typename Parameter_t>
    // inline void from_json(const json & j, StrongType<T, Parameter_t> & st)
    //{
    //    j.at("value").get_to(st.m_value);
    //}

    template <typename T, typename Parameter_t>
    inline std::ostream & operator<<(std::ostream & os, const StrongType<T, Parameter_t> & rhs)
    {
        os << rhs.get();
        return os;
    }
} // namespace util

#endif // STRONGTYPE_HPP_INCLUDED
