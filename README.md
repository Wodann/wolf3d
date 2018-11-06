# wolf3d

The code was built and tested using Visual Studio 2017 (v15.9.0 preview 4.0) and GCC 7.3.0; requiring support for C++17.

### Thirdparty
Used a thirdparty [interval tree library](https://github.com/ekg/intervaltree), modified to support lookup of intersected intervals.

### Build

  - Checkout repository
  - Run `git submodule update --init`
  - Run CMake (v3.5.0 or higher)
  - Compile with GCC or MSVC depending on your operating system
  
### Test

To test the basic requirements, run the `basic` executable. When prompted provide the path to the `data/basic.txt` file. Similary, to test the advanced requirements, run the `advanced` executable. When prompted provide the path to the `data/advanced.txt` file.
