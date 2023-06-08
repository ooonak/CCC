# CCC
C's Command &amp; Control

## Build and run
```bash
$ mkdir build
$ cd build
$ cmake -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Debug ..
$ cmake --build .
$ ./src/ccc
```

```bash
$ mkdir build_emscriptem
$ cd build_emscriptem
$ emcmake cmake -DMSGPACK_USE_BOOST=OFF ..
$ make -j $(nproc)

$ cd src/
$ python ./run_webassembly.py
```
