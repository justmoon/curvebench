# Curvebench

A quick comparison benchmark between Ed25519 (implementation by DJB et al) and secp256k1 (implementation by Pieter Wuille et al).

# Instructions

``` sh
# Build secp256k1
cd src/secp256k1
aclocal
autoreconf --install
automake
./configure
make
cd ../..

# Build rest
cmake .
make

# Run benchmark
./benchmark
