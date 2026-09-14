# dupfind

![ci](badge)

A fast CLI tool for finding duplicate files, written in C++17 with no external dependencies.

## Why

The naive approach hashes every file. `dupfind` uses three filters to avoid unnecessary work:

## Demo

[asciinema GIF or terminal screenshot]

## How it works

1. Group files by size
2. Compute a quick hash of the first 4 KB
3. Compute the full hash only for files that are still possible duplicates

## Results

Tested on 120,412 files (38 GB) on an HDD:

* **dupfind:** 6.2s
* **`find | md5sum | sort`:** 94s
* **Duplicate data found:** 3.1 GB

## Build

```bash
git clone ...
cmake -B build
cmake --build build -j
ctest --test-dir build
```

## Usage

```text
dupfind <dir> [--min-size N] [--format text|json|csv]
```

## Limitations

FNV-1a is not a cryptographic hash. For forensic use, use SHA-256 instead.

`dupfind` does not perform a byte-by-byte comparison after hashing, so there is a theoretical possibility of hash collisions.

## License

MIT
