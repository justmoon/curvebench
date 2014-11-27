include_directories(
  ${PROJECT_SOURCE_DIR}/src/chayai/src
  ${PROJECT_SOURCE_DIR}/src/ed25519-donna
  ${PROJECT_SOURCE_DIR}/src/secp256k1/include
)

set(CMAKE_C_FLAGS "-std=c99 -m64 -O3")
set(CMAKE_CXX_FLAGS "-std=c++11 -m64 -O3 -fpermissive")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

add_custom_command(
  OUTPUT ${PROJECT_SOURCE_DIR}/src/secp256k1/libsecp256k1.a
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src/secp256k1
  COMMAND ./autogen.sh && ./configure --enable-endomorphism CFLAGS="-O3" && make && cp .libs/libsecp256k1.a .
)

add_executable(benchmark
  main.c
  secp256k1.c
  ed25519.c
  ${PROJECT_SOURCE_DIR}/src/ed25519-donna/ed25519.c
  ${PROJECT_SOURCE_DIR}/src/secp256k1/libsecp256k1.a
)

target_link_libraries(benchmark
  chayai
  crypto
  ${PROJECT_SOURCE_DIR}/src/secp256k1/libsecp256k1.a
  gmp
)
