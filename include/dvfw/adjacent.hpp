#ifndef DVFW_ADJACENT_HPP
#define DVFW_ADJACENT_HPP

#include <dvfw/impl/concepts.hpp>
#include <iterator>

namespace dvfw
{
    template<typename Range>
    struct adjacent_range
    {
        Range const& range;
        explicit adjacent_range(Range const& range) : range(range) {}
    };
    
    template<typename Range>
    auto adjacent(Range&& range)
    {
        return adjacent_range<std::decay_t<Range>>(FWD(range));
    }
    
    template<typename Range, typename Pipeline, detail::IsAPipeline<Pipeline> = true>
    void operator>>= (adjacent_range<Range> rangesHolder, Pipeline&& pipeline)
    {
        auto& range = rangesHolder.range;
        
        using std::begin;
        using std::end;
        
        auto first = begin(range);
        auto second = begin(range);

        if (second != end(range))
        {
            second++;
        }

        while (second != end(range))
        {
            send(*first, *second, pipeline);

            first++;
            second++;
        }
    }
} // namespace dvfw

#endif /* DVFW_ADJACENT_HPP */