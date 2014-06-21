include_directories(
  ${PROJECT_SOURCE_DIR}/src
)

include(CheckLibraryExists)
CHECK_LIBRARY_EXISTS(rt clock_gettime "time.h" NEED_RT_LIB)

if(${NEED_RT_LIB}) 
    set(EXT_LIB "rt")
else()
    set(EXT_LIB "")
endif()

add_executable(sample
  delivery_man_benchmark.c
  delivery_man_benchmark_with_fixture.c
  delivery_man_benchmark_parameterized.c
  delivery_man_benchmark_parameterized_with_fixture.c
  delivery_man_sleep.c
  main.c
)

target_link_libraries(sample
  chayai
  ${EXT_LIB}
)
