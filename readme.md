# Simple File Compressor

> A lightweight file compression and decompression tool built from scratch in C++ using the Huffman coding algorithm.

## Project Status: Active Development 🚀

## 🛠 Features & Optimizations

### Core Logic & Optimizations
- **Data Structures:** Custom Node and Tree structures implemented.
- **Huffman Algorithm:** Priority Queue implementation to build the optimal Huffman Tree.
- **Optimization:** Replaced `std::map` with **Static Arrays (Lookup Tables)** for encoding/decoding to achieve **O(1)** access time and minimize memory overhead.
- **Frequency Analysis:** Character counting using direct array indexing.

### Compression (Encoding)
- **Bitwise Manipulation:** Packing variable-length bit codes into compact bytes using a custom `BitWriter`.
- **File Header:** Efficiently storing the Frequency Table (Metadata) to reconstruct the tree later.
- **Binary I/O:** Writing compressed data directly in binary mode.

### Decompression (Decoding)
- **Header Parsing:** Reading metadata to rebuild the exact Huffman Tree used for compression.
- **Bitwise Decoding:** Reading raw bits stream to traverse the tree and restore original characters.
- **Padding Handling:** logic to handle and ignore padding bits at the end of the file.

## Project Structure

- `Huffmantree.h/cpp`: Manages the tree construction, recursive code generation, and array-based lookup table.
- `Bitwriter.h/cpp`: Handles bit-level buffer management for writing.
- `main.cpp`: CLI entry point handling the flow for both Compression and Decompression.

## How it works

1.  **Compression:** Input Text -> Frequency Array -> Huffman Tree -> Bit Codes Array -> Binary File (Header + Body).
2.  **Decompression:** Binary File -> Read Header -> Reconstruct Tree -> Read Bits & Traverse Tree -> Original Text.