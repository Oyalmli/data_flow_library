/**
 * @file dfl.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Entry point for the library
 * 
 * Select which parts of the framework are to be exported
 * 
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DFL_HPP
#define DFL_HPP

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "dfl/gen/impl/base_generator.hpp"

#include "dfl/gen/adjacent.hpp"
#include "dfl/gen/counter.hpp"
#include "dfl/gen/file.hpp"
#include "dfl/mod/noise.hpp"
#include "dfl/mod/flag.hpp"
#include "dfl/mod/random_err.hpp"
#include "dfl/mod/take.hpp"
#include "dfl/mod/repeat.hpp"
#include "dfl/gen/range.hpp"
#include "dfl/gen/sine.hpp"
#include "dfl/gen/value.hpp"
#include "dfl/impl/operator.hpp"
#include "dfl/impl/send.hpp"
#include "dfl/pipe/chunks.hpp"
#include "dfl/pipe/drop.hpp"
#include "dfl/pipe/drop_while.hpp"
#include "dfl/pipe/filter.hpp"
#include "dfl/rdir/fork.hpp"
#include "dfl/pipe/get_var.hpp"
#include "dfl/pipe/intersperse.hpp"
#include "dfl/pipe/moving_avg.hpp"
#include "dfl/rdir/partition.hpp"
#include "dfl/pipe/scanl.hpp"
#include "dfl/pipe/set_state.hpp"
#include "dfl/pipe/set_var.hpp"
#include "dfl/pipe/side_effect.hpp"
#include "dfl/pipe/stride.hpp"
#include "dfl/pipe/take.hpp"
#include "dfl/pipe/tap.hpp"
#include "dfl/pipe/tee.hpp"
#include "dfl/pipe/transform.hpp"
#include "dfl/pipe/transform_s.hpp"
#include "dfl/sink/for_each.hpp"
#include "dfl/sink/hole.hpp"
#include "dfl/sink/histogram.hpp"
#include "dfl/sink/min.hpp"
#include "dfl/sink/max.hpp"
#include "dfl/sink/print.hpp"
#include "dfl/sink/printf.hpp"
#include "dfl/sink/push_back.hpp"
#include "dfl/sink/to_out_stream.hpp"
#include "dfl/sink/set_var.hpp"
#include "dfl/sink/sum.hpp"
#include "dfl/util/IO.hpp"

#include "dfl/gen/mux.hpp"

#include "dfl/helpers/functions.hpp"
#endif /* DFL_HPP */
