# Curvebench

A quick comparison benchmark between Ed25519 (implementation by DJB et al) and secp256k1 (implementation by Pieter Wuille et al).

# Instructions

You need G++, CMake 2.6, OpenSSL and YASM.

``` sh
# Build
cmake .
make

# Run benchmark
./benchmark
```
# Results

See [benchmark.html](http://justmoon.github.io/curvebench/benchmark.html)