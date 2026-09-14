# dupfind

`dupfind` is a fast command-line tool for finding duplicate files, written in C++17.

It reduces unnecessary hashing by progressively filtering files based on their size, a quick hash, and finally their full-file hash.

## Build

Clone the repository and configure the project with CMake:

```bash
git clone https://github.com/DaliborMax/dupfind/
cd dupfind

cmake -B build
cmake --build build -j
```

Run the test suite with:

```bash
ctest --test-dir build
```

## Run
# On Linux/macOS/WSL:
./build/dupfind path/to/folder

# On Windows (Command Prompt/PowerShell):
.\build/dupfind.exe path/to/folder

## Features

* Written in C++17
* Groups files by file size before hashing
* Computes a full hash only for files that remain possible duplicates
* Reports duplicate groups and wasted disk space
* Supports recursive directory scanning
* Unit tests with GoogleTest
* CMake-based build system

## How it works

`dupfind` uses several filtering stages:

1. **File size**

   Files with different sizes cannot be duplicates, so they are immediately separated.

2. **Full hash**

   Only files that still match after the previous filters are fully hashed.

3. **Duplicate groups**

   Files with the same size and full hash are reported as duplicates.

This avoids reading the entire contents of files that can already be ruled out by cheaper checks.

## Example

Running `dupfind` on a directory produces output similar to:

```text
File size: 748 bytes (Hash: 16911946311754036552)
  - dupfind/build_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitclone-lastrun.txt
  - dupfind/build_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitinfo.txt
----------------------------------------
File size: 86 bytes (Hash: 10865774324573571303)
  - dupfind/build/CMakeFiles/cmake.check_cache
  - dupfind/build_deps/googletest-subbuild/CMakeFiles/cmake.check_cache
----------------------------------------
File size: 387 bytes (Hash: 15360795553981820299)
  - dupfind/build/CMakeFiles/4.1.2/CMakeSystem.cmake
  - dupfind/build_deps/googletest-subbuild/CMakeFiles/4.1.2/CMakeSystem.cmake
----------------------------------------
File size: 41 bytes (Hash: 5282075761900802357)
  - dupfind/.git/refs/heads/main
  - dupfind/.git/refs/remotes/origin/main
----------------------------------------
File size: 4726 bytes (Hash: 4283462961482075888)
  - dupfind/.git/hooks/fsmonitor-watchman.sample
  - dupfind/build_deps/googletest-src/.git/hooks/fsmonitor-watchman.sample

Total wasted space due to duplicates: 27731 bytes.
```

The final line shows the total amount of disk space occupied by redundant copies.


## Project structure

```text
dupfind/
├── .github/
├── └──workflows/
        └──ci.yml
├──app
    └──main.cpp
├── include/
│   └── dupfind/
├── src/
├── tests/
├── CMakeLists.txt
└── README.md
```

## Testing

The project uses [GoogleTest](https://github.com/google/googletest) for unit testing.

Tests cover components including file scanning, hashing, grouping, and duplicate detection.

Run all tests with:

```bash
ctest --test-dir build
```

## Limitations

The current implementation uses **FNV-1a** for hashing. FNV-1a is not a cryptographic hash and SHOULD NOT BE USED as a security or forensic hash.

`dupfind` currently considers files with the same size and hash to be duplicates without performing a final byte-by-byte comparison. Although hash collisions are unlikely in normal use, they are theoretically possible.

For forensic or security-sensitive applications, a cryptographic hash such as SHA-256 and a final byte-by-byte comparison should be used.

## License

MIT
