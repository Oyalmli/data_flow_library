#ifndef DFL_OUTPUT_ITERATOR_HPP
#define DFL_OUTPUT_ITERATOR_HPP

#include <iterator>

#include "dfl/helpers/FWD.hpp"
#include "dfl/helpers/crtp.hpp"
#include "dfl/helpers/assignable.hpp"
#include "dfl/impl/send.hpp"

namespace dfl {
struct dfl_base {};

template <typename Pipeline>
struct pipeline_proxy {
    template <typename T>
    pipeline_proxy& operator=(T&& input) {
        send(FWD(input), pipeline_);
        return *this;
    }

    explicit pipeline_proxy(Pipeline& pipeline) : pipeline_(pipeline) {}

   private:
    Pipeline& pipeline_;
};

template <typename Derived>
struct pipeline_base : detail::crtp<Derived, pipeline_base> {
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;

    Derived& operator++() { return this->derived(); }
    Derived& operator++(int) {
        ++this->derived();
        return this->derived();
    }
    pipeline_proxy<Derived> operator*() { return pipeline_proxy<Derived>(this->derived()); }
};
}  // namespace dfl

#endif /* DFL_OUTPUT_ITERATOR_HPP */
