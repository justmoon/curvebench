include_directories(
  ${PROJECT_SOURCE_DIR}/src/hayai/src
  ${PROJECT_SOURCE_DIR}/src/ed25519/src
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

add_executable(benchmark
  secp256k1.cpp

  ed25519.cpp
  ${PROJECT_SOURCE_DIR}/src/ed25519/src/fe.c
  ${PROJECT_SOURCE_DIR}/src/ed25519/src/ge.c
  ${PROJECT_SOURCE_DIR}/src/ed25519/src/sc.c
  ${PROJECT_SOURCE_DIR}/src/ed25519/src/seed.c
  ${PROJECT_SOURCE_DIR}/src/ed25519/src/keypair.c
  ${PROJECT_SOURCE_DIR}/src/ed25519/src/sha512.c
  ${PROJECT_SOURCE_DIR}/src/ed25519/src/sign.c
  ${PROJECT_SOURCE_DIR}/src/ed25519/src/verify.c
)

target_link_libraries(benchmark
  hayai_main
)
