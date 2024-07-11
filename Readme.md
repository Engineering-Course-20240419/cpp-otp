# Linux

Please make sure you have `gcc`, `make` and `autotools` installed

Build cpputest first:
```shell
cd cpputest
./configure --disable-longlong
make tdd
```

Build and run the test:
```shell
make all
```

Build and run the program:
```shell
make main
```

Get the coverage report (run below on the machine with lcov):
```shell
lcov --capture --directory build/test-obj/main --output-file coverage.info --ignore-errors range --exclude '/usr/*'
genhtml coverage.info --output-directory report --ignore-errors range
```

# VC++ 6.0

Please make sure you have `cmake` and `VC++ 6.0` installed

Build:
```shell
mkdir cmake_build
cd cmake_build
cmake ..
cmake --build .
```

Run the test:
```shell
cd test
cpp_otp_test.exe
```

Run the program:
```shell
cd main
cpp_otp.exe
```
