#ifndef DVFW_CRTP_HPP
#define DVFW_CRTP_HPP

namespace dvfw::detail {

template <typename T, template <typename> class crtpType>
struct crtp {
  T& derived() { return static_cast<T&>(*this); }
  T const& derived() const { return static_cast<T const&>(*this); }

 private:
  crtp() {}
  friend crtpType<T>;
};

}  // namespace dvfw::detail

#endif /* DVFW_CRTP_HPP */