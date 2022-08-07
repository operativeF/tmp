#  Copyright 2021 Thomas Figueroa.
#  Distributed under the Boost Software License, Version 1.0.
#
#  See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt


set(TMP_ALGO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/algorithm)
set(TMP_DETAIL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/detail)
set(TMP_SEQ_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sequence)
set(TMP_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/base)
set(TMP_UTILS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/utils)

set(TMP_UTILS_IXX
    ${TMP_UTILS_DIR}/Boost.TMP-TestHelpers.ixx
)

set(TMP_ALGO_IXX
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.AllOf.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.AnyOf.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Clamp.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Contains.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.CountIf.ixx
    # ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Extrema.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Filter.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.FindIf.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Flatten.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.FoldLeft.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.FoldRight.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Gather.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.NoneOf.ixx
    # ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Pairing.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Partition.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Product.ixx
    # ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.RangeMath.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.RemoveIf.ixx
    # ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.RemovePairs.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.ReplaceIf.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Sort.ixx
    # ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.SymmetricDifference.ixx
    ${TMP_ALGO_DIR}/Boost.TMP-Algorithm.Transform.ixx
)

set(TMP_MAIN_IXX
    ${TMP_BASE_DIR}/Boost.TMP-Base.Always.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Bool.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Byte.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Call.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Char.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Comparison.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Dispatch.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Foldey.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Identity.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.If.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Integral.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Lift.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.List.ixx
    # ${TMP_BASE_DIR}/Boost.TMP-Base.ListOperations.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Logic.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Map.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Maybe.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Nothing.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Result.ixx
    ${TMP_BASE_DIR}/Boost.TMP-Base.Try.ixx
)

set(TMP_SEQ_IXX
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.Drop.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.Each.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.Erase.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.Index.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.Insert.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.Join.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.MakeSequence.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.PopBack.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.PopFront.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.PushBack.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.PushFront.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.RepeatSequence.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.Reverse.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.Rotate.ixx
    # ${TMP_SEQ_DIR}/Boost.TMP-Sequence.Set.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.Size.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.Swap.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.Take.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.Tee.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.Unpack.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.ZipWithIndex.ixx
    ${TMP_SEQ_DIR}/Boost.TMP-Sequence.Zip.ixx
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
        ${TMP_DETAIL_IXX}
        ${TMP_SEQ_IXX}
        ${TMP_BASE_IXX}
        ${TMP_UTILS_IXX}
)

if(MSVC)
    target_compile_options(boost_tmp PRIVATE /reference std=C:/dev/STL/std.ifc)
endif()
