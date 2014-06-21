include_directories(
  ${PROJECT_SOURCE_DIR}/src/chayai/src
#  ${PROJECT_SOURCE_DIR}/src/ed25519/src
  ${PROJECT_SOURCE_DIR}/src/ed25519-donna
  ${PROJECT_SOURCE_DIR}/src/secp256k1/include
  ${PROJECT_SOURCE_DIR}/src/secp256k1/src
)

set(CMAKE_C_FLAGS "-std=c99 -m64 -O3")
set(CMAKE_CXX_FLAGS "-std=c++11 -m64 -O3 -fpermissive")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

SET_SOURCE_FILES_PROPERTIES(
  ${PROJECT_SOURCE_DIR}/src/secp256k1/src/.libs/field_5x52_asm.o
  PROPERTIES
  EXTERNAL_OBJECT true
  GENERATED true
)

add_executable(benchmark
  main.c

  secp256k1.c
  ${PROJECT_SOURCE_DIR}/src/secp256k1/src/field_5x52_asm.o

#  ed25519.cpp
#  ${PROJECT_SOURCE_DIR}/src/ed25519/src/fe.c
#  ${PROJECT_SOURCE_DIR}/src/ed25519/src/ge.c
#  ${PROJECT_SOURCE_DIR}/src/ed25519/src/sc.c
#  ${PROJECT_SOURCE_DIR}/src/ed25519/src/seed.c
#  ${PROJECT_SOURCE_DIR}/src/ed25519/src/keypair.c
#  ${PROJECT_SOURCE_DIR}/src/ed25519/src/sha512.c
#  ${PROJECT_SOURCE_DIR}/src/ed25519/src/sign.c
#  ${PROJECT_SOURCE_DIR}/src/ed25519/src/verify.c

  ed25519.c
  ${PROJECT_SOURCE_DIR}/src/ed25519-donna/ed25519.c
)

target_link_libraries(benchmark
  chayai
  gmp
  ssl
  crypto
)
