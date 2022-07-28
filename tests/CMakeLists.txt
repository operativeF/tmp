
add_executable(tmp_test)

target_sources(tmp_test
    PRIVATE
        test.cpp

    PRIVATE
        FILE_SET boost_tmp_test_modules TYPE CXX_MODULES FILES
        Boost.TMP.Tests-AllOf.ixx
        Boost.TMP.Tests-AnyOf.ixx
        Boost.TMP.Tests-Clamp.ixx
        Boost.TMP.Tests-Contains.ixx
        Boost.TMP.Tests-CountIf.ixx
        Boost.TMP.Tests-Drop.ixx
        Boost.TMP.Tests-Each.ixx
        Boost.TMP.Tests-Erase.ixx
        # Boost.TMP.Tests-Extrema.ixx
        Boost.TMP.Tests-Filter.ixx
        Boost.TMP.Tests-FindIf.ixx
        # Boost.TMP.Tests-Flatten.ixx
        Boost.TMP.Tests-FoldLeft.ixx
        Boost.TMP.Tests-FoldRight.ixx
        Boost.TMP.Tests-Index.ixx
        Boost.TMP.Tests-Insert.ixx
        Boost.TMP.Tests-Join.ixx
        Boost.TMP.Tests-Logic.ixx
        Boost.TMP.Tests-NoneOf.ixx
        Boost.TMP.Tests-Partition.ixx
        Boost.TMP.Tests-PopFront.ixx
        # Boost.TMP.Tests-Product.ixx
        Boost.TMP.Tests-PushBack.ixx
        Boost.TMP.Tests-PushFront.ixx
        # Boost.TMP.Tests-RangeMath.ixx
        Boost.TMP.Tests-RemoveIf.ixx
        Boost.TMP.Tests-RepeatSequence.ixx
        Boost.TMP.Tests-ReplaceIf.ixx
        Boost.TMP.Tests-Reverse.ixx
        Boost.TMP.Tests-Rotate.ixx
        # Boost.TMP.Tests-Set.ixx
        Boost.TMP.Tests-Size.ixx
        Boost.TMP.Tests-Sort.ixx
        Boost.TMP.Tests-Swap.ixx
        Boost.TMP.Tests-Take.ixx
        Boost.TMP.Tests-Tee.ixx
        Boost.TMP.Tests-Transform.ixx
        Boost.TMP.Tests-Try.ixx
        
        Boost.TMP.Tests.ixx
)

if(MSVC)
    target_compile_options(tmp_test PRIVATE /reference std=C:/dev/STL/std.ifc)
endif()

target_link_libraries(tmp_test
    PRIVATE
        boost_tmp
)
