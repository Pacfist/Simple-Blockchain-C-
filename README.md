# 🧱 Simple Blockchain in C++

This is a minimal blockchain implementation in C++ written for learning purposes. It simulates how blocks are linked using hashes and how tampering with the chain can be detected.

## 🚀 Features

- Each block contains:
  - `id`
  - `name`
  - `hash` (calculated from the block’s contents)
  - `prevHash` (the hash of the previous block)
- Blocks are linked via hashes
- You can:
  - Add new blocks
  - Print the blockchain visually
  - Check the integrity of the chain

If any block is modified, the `checkBlockChain()` function will detect the inconsistency.

## 🛠️ Build & Run

```bash
g++ main.cpp -o main
./main
