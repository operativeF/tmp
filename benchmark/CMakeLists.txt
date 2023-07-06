
# Tell CMake to run python from the directory where this CMakeLists file exists.
# execute_process(COMMAND python mako_file_generator.py 
#     WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

# if(NOT EXISTS Boost.TMP-Bench.Clamp.cpp)
#     file(REMOVE Boost.TMP-Bench.Clamp.cpp)
# endif()

add_library(clamp_bench)

target_sources(clamp_bench
    PRIVATE
        Boost.TMP-Bench.Clamp.cpp
)

target_link_libraries(clamp_bench PRIVATE boost_tmp)
