#ifndef DVFW_HPP
#define DVFW_HPP

#include "dvfw/operator.hpp"
#include "dvfw/send.hpp"

#include "dvfw/gen/base.hpp"
#include "dvfw/gen/file.hpp"
#include "dvfw/gen/modifyer/noise.hpp"
#include "dvfw/gen/modifyer/random_err.hpp"
#include "dvfw/gen/range.hpp"
#include "dvfw/gen/value.hpp"
#include "dvfw/operator.hpp"
#include "dvfw/pipe/chunks.hpp"
#include "dvfw/pipe/drop.hpp"
#include "dvfw/pipe/drop_while.hpp"
#include "dvfw/pipe/filter.hpp"
#include "dvfw/pipe/fork.hpp"
#include "dvfw/pipe/intersperse.hpp"
#include "dvfw/pipe/partition.hpp"
#include "dvfw/pipe/scanl.hpp"
#include "dvfw/pipe/set_state.hpp"
#include "dvfw/pipe/take.hpp"
#include "dvfw/pipe/tee.hpp"
#include "dvfw/pipe/transform.hpp"
#include "dvfw/pipe/transform_s.hpp"
#include "dvfw/sink/for_each.hpp"
#include "dvfw/sink/hole.hpp"
#include "dvfw/sink/print.hpp"
#include "dvfw/sink/printf.hpp"
#include "dvfw/sink/push_back.hpp"
#include "dvfw/sink/to_out_stream.hpp"

#endif /* DVFW_HPP */