#ifndef DFL_CRTP_HPP
#define DFL_CRTP_HPP

namespace dfl::detail {

template <typename T, template <typename> class crtpType>
struct crtp {
  T& derived() { return static_cast<T&>(*this); }
  T const& derived() const { return static_cast<T const&>(*this); }

 private:
  crtp() {}
  friend crtpType<T>;
};

}  // namespace dfl::detail

#endif /* DFL_CRTP_HPP */