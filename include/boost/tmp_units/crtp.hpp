#ifndef CRTP_HPP
#define CRTP_HPP

namespace boost::tmp::units
{
    template <typename T, template<typename> class crtpType>
    struct crtp
    {
        T& underlying() { return static_cast<T&>(*this); }
        T const& underlying() const { return static_cast<T const&>(*this); }
    };
    template <typename T, typename U, typename Op, template<typename...> class crtpType>
    struct crtp_d
    {
        using rtype = call_<composite_<Op>, T, U>;
        rtype& underlying() { return static_cast<rtype&>(*this); }
        rtype const& underlying() const { return static_cast<rtype const&>(*this); }
    };
} // namespace boost::tmp::units

#endif
