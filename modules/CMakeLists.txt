#  Copyright 2021 Thomas Figueroa.
#  Distributed under the Boost Software License, Version 1.0.
#
#  See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt


set(TMP_ALGO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/algorithm)
set(TMP_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/base)

set(TMP_ALGO_IXX
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Chunk.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Clamp.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Counted.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Drop.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Each.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Erase.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Filter.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Flatten.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.FoldLeft.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.FoldRight.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Foldey.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.FunctionIf.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Index.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Insert.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Join.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Logic.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.MakeSequence.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.NthValues.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Partition.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Product.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.PushPop.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Reverse.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Rotate.ixx
    # ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Set.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Size.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Slice.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Slide.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Split.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Sort.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Stride.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Swap.ixx
    # ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.SymmetricDifference.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Take.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Tee.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Trim.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Transform.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Unique.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Unpack.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Zip.ixx
)

set(TMP_MAIN_IXX
    # ${TMP_BASE_DIR}/Boost.TMP-Base.ListOperations.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Map.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Types.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Try.ixx
)

set(TMP_BASE_IXX
    ${CMAKE_CURRENT_SOURCE_DIR}/Boost.TMP.ixx
)

add_library(boost_tmp STATIC)

target_sources(boost_tmp
    PUBLIC
        FILE_SET boost_tmp_modules TYPE CXX_MODULES FILES
        ${TMP_ALGO_IXX}
        ${TMP_MAIN_IXX}
        ${TMP_BASE_IXX}
)

if(MSVC)
    target_compile_options(boost_tmp PRIVATE /reference std=C:/dev/STL/std.ifc)
endif()
