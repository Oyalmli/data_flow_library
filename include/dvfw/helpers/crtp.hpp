#ifndef DVFW_CRTP_HPP
#define DVFW_CRTP_HPP

namespace dvfw {
namespace detail {

template <typename T, template <typename> class crtpType>
struct crtp {
    T& derived() { return static_cast<T&>(*this); }
    T const& derived() const { return static_cast<T const&>(*this); }

   private:
    crtp() {}
    friend crtpType<T>;
};

}  // namespace detail
}  // namespace dvfw

#endif /* DVFW_CRTP_HPP */