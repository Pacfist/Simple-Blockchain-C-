# 🧱 Simple Blockchain Simulator in C++

This is a minimal blockchain simulator written in C++ for educational purposes. It allows users to simulate a blockchain by creating addresses, making transactions, and mining blocks with basic hashing logic.

## 💡 Features

- Create and manage wallet addresses
- Simulate money transfers
- Mine new blocks containing transactions
- View blockchain structure and block data
- Verify blockchain integrity
- CLI-based interactive interface

## 📁 Files

- `main.cpp` — contains all the classes and logic to run the blockchain.

## 🔧 How It Works

- **Block**: Contains metadata (ID, hash, prevHash, name) and a list of transactions.
- **Transaction**: Represents a transfer between two addresses.
- **Blockchain**: A list of blocks, each hashed based on its content and previous hash.
- **addressToBalance**: A global map tracking the balance of each address.

## 🛠 Future Improvements

- Add timestamps to blocks
- Implement digital signatures
- Add persistent storage
- Improve input validation and error handling


