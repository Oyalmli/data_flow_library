/**
 * @file dvfw.hpp
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
#ifndef DVFW_HPP
#define DVFW_HPP

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "dvfw/gen/gen_iter.hpp"
#include "dvfw/gen/impl/base_generator.hpp"

#include "dvfw/gen/file.hpp"
#include "dvfw/gen/impl/base_iterator.hpp"
#include "dvfw/gen/modifyer/noise.hpp"
#include "dvfw/gen/modifyer/random_err.hpp"
#include "dvfw/gen/modifyer/take.hpp"
#include "dvfw/gen/modifyer/repeat.hpp"
#include "dvfw/gen/range.hpp"
#include "dvfw/gen/sine.hpp"
#include "dvfw/gen/value.hpp"
#include "dvfw/impl/operator.hpp"
#include "dvfw/impl/send.hpp"
#include "dvfw/pipe/chunks.hpp"
#include "dvfw/pipe/drop.hpp"
#include "dvfw/pipe/drop_while.hpp"
#include "dvfw/pipe/filter.hpp"
#include "dvfw/pipe/fork.hpp"
#include "dvfw/pipe/intersperse.hpp"
#include "dvfw/pipe/moving_avg.hpp"
#include "dvfw/gen/mux.hpp"
#include "dvfw/pipe/partition.hpp"
#include "dvfw/pipe/scanl.hpp"
#include "dvfw/pipe/set_state.hpp"
#include "dvfw/pipe/take.hpp"
#include "dvfw/pipe/tap.hpp"
#include "dvfw/pipe/tee.hpp"
#include "dvfw/pipe/transform.hpp"
#include "dvfw/pipe/transform_s.hpp"
#include "dvfw/sink/for_each.hpp"
#include "dvfw/sink/hole.hpp"
#include "dvfw/sink/print.hpp"
#include "dvfw/sink/printf.hpp"
#include "dvfw/sink/push_back.hpp"
#include "dvfw/sink/to_out_stream.hpp"
#include "dvfw/util/IO.hpp"
#include "dvfw/gen/adjacent.hpp"
#endif /* DVFW_HPP */