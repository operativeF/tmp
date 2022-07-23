#  Copyright 2021 Thomas Figueroa.
#  Distributed under the Boost Software License, Version 1.0.
#
#  See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt


set(TMP_ALGO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/algorithm)
set(TMP_DETAIL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/detail)
set(TMP_SEQ_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sequence)
set(TMP_MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(TMP_ALGO_IXX
    ${TMP_ALGO_DIR}/all_of.ixx
    ${TMP_ALGO_DIR}/any_of.ixx
    ${TMP_ALGO_DIR}/clamp.ixx
    ${TMP_ALGO_DIR}/contains.ixx
    ${TMP_ALGO_DIR}/count_if.ixx
    ${TMP_ALGO_DIR}/extrema.ixx
    ${TMP_ALGO_DIR}/filter.ixx
    ${TMP_ALGO_DIR}/find_if.ixx
    ${TMP_ALGO_DIR}/flatten.ixx
    ${TMP_ALGO_DIR}/fold_left.ixx
    ${TMP_ALGO_DIR}/fold_right.ixx
    ${TMP_ALGO_DIR}/gather.ixx
    ${TMP_ALGO_DIR}/none_of.ixx
    ${TMP_ALGO_DIR}/pairing.ixx
    ${TMP_ALGO_DIR}/partition.ixx
    ${TMP_ALGO_DIR}/product.ixx
    ${TMP_ALGO_DIR}/range_math.ixx
    ${TMP_ALGO_DIR}/remove_if.ixx
    ${TMP_ALGO_DIR}/remove_pairs.ixx
    ${TMP_ALGO_DIR}/replace_if.ixx
    ${TMP_ALGO_DIR}/sort.ixx
    ${TMP_ALGO_DIR}/symmetric_difference.ixx
    ${TMP_ALGO_DIR}/transform.ixx
    ${TMP_ALGO_DIR}/tmp_algorithm.ixx
)

set(TMP_MAIN_IXX
    ${TMP_MAIN_DIR}/always.ixx
    ${TMP_MAIN_DIR}/call.ixx
    ${TMP_MAIN_DIR}/comparison.ixx
    ${TMP_MAIN_DIR}/decay.ixx
    ${TMP_MAIN_DIR}/identity.ixx
    ${TMP_MAIN_DIR}/if.ixx
    ${TMP_MAIN_DIR}/lift.ixx
    ${TMP_MAIN_DIR}/list_operations.ixx
    ${TMP_MAIN_DIR}/logic.ixx
    ${TMP_MAIN_DIR}/tmp_base.ixx
    ${TMP_MAIN_DIR}/try.ixx
    ${TMP_MAIN_DIR}/vocabulary.ixx
)

set(TMP_DETAIL_IXX                                                                                                                                                     
    ${TMP_DETAIL_DIR}/detail.ixx
    ${TMP_DETAIL_DIR}/dispatch.ixx
)

set(TMP_SEQ_IXX
    ${TMP_SEQ_DIR}/container.ixx
    ${TMP_SEQ_DIR}/drop.ixx
    ${TMP_SEQ_DIR}/each.ixx
    ${TMP_SEQ_DIR}/erase.ixx
    ${TMP_SEQ_DIR}/index.ixx
    ${TMP_SEQ_DIR}/insert.ixx
    ${TMP_SEQ_DIR}/join.ixx
    ${TMP_SEQ_DIR}/make_sequence.ixx
    ${TMP_SEQ_DIR}/pop_back.ixx
    ${TMP_SEQ_DIR}/pop_front.ixx
    ${TMP_SEQ_DIR}/push_back.ixx
    ${TMP_SEQ_DIR}/push_front.ixx
    ${TMP_SEQ_DIR}/repeat_sequence.ixx
    ${TMP_SEQ_DIR}/reverse.ixx
    ${TMP_SEQ_DIR}/rotate.ixx
    ${TMP_SEQ_DIR}/sequence.ixx
    ${TMP_SEQ_DIR}/set.ixx
    ${TMP_SEQ_DIR}/size.ixx
    ${TMP_SEQ_DIR}/swap.ixx
    ${TMP_SEQ_DIR}/take.ixx
    ${TMP_SEQ_DIR}/tee.ixx
    ${TMP_SEQ_DIR}/unpack.ixx
    ${TMP_SEQ_DIR}/zip_with_index.ixx
    ${TMP_SEQ_DIR}/zip.ixx
)

set(TMP_BASE_IXX
    ${CMAKE_CURRENT_SOURCE_DIR}/tmp.ixx
)

add_library(boost_tmp STATIC)

target_sources(boost_tmp
    PUBLIC
        FILE_SET boost_tmp_modules TYPE CXX_MODULES FILES
        ${TMP_ALGO_IXX}
        ${TMP_MAIN_IXX}
        ${TMP_DETAIL_IXX}
        ${TMP_SEQ_IXX}
        ${TMP_BASE_IXX}
)
