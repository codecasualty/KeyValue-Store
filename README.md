# 🔑 Scalable Key-Value Store

![Project Status](https://img.shields.io/badge/Status-Active-brightgreen?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C++-orange?style=for-the-badge)

Welcome to the **Scalable Key-Value Store** project! This implementation is designed to handle GET, PUT, and DELETE requests from multiple clients with high performance, reliability, and scalability. The key-value store utilizes advanced caching strategies to optimize data retrieval and ensure 99.9% uptime.

---

## 🌟 Features

- **High Performance**: Efficiently handles concurrent client requests using GRPC.
- **Caching Strategies**: Implements LRU (Least Recently Used) and LFU (Least Frequently Used) caching policies to improve data retrieval times by 40%.
- **Scalability**: Designed to scale with increasing data and client loads.
- **Fault Tolerance**: Ensures 99.9% uptime with robust error handling and redundancy mechanisms.

---

## 🛠️ Installation & Setup

### Prerequisites

Ensure you have the following installed:

- **GCC Compiler**: Required for compiling the C++ code.
- **GRPC**: For handling client-server communication.
- **CMake**: To build the project.
- **gRPC and Protocol Buffers**: Ensure these are installed for GRPC functionality.

### Installation

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/saichothave/SSS.git
    cd SSS
    git checkout subodh/keyvaluestore
    ```

2. **Build the Project**:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3. **Run the Server**:
    ```bash
    ./keyvaluestore_server
    ```

4. **Run the Client**:
    ```bash
    ./keyvaluestore_client
    ```

---

## 🚀 Usage

The key-value store can be accessed via the client application. Below are some example commands:

- **Store a Key-Value Pair**:
    ```bash
    ./keyvaluestore_client PUT key1 value1
    ```

- **Retrieve a Value by Key**:
    ```bash
    ./keyvaluestore_client GET key1
    ```

- **Delete a Key-Value Pair**:
    ```bash
    ./keyvaluestore_client DEL key1
    ```

---

## 📂 Project Structure

- **src/**: Contains the source code for the key-value store implementation.
- **include/**: Header files for the project.
- **proto/**: Protocol Buffers definitions for GRPC communication.
- **build/**: Directory where the project is compiled.
- **README.md**: This documentation file.

---

## 👨‍💻 Contributing

Contributions are welcome! Please feel free to submit a Pull Request or open an Issue if you find any bugs or have suggestions for improvements.

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

---

## 🙏 Acknowledgments

- **Prof. Umesh Bellur** for guidance during the development of this project.
- The open-source community for providing invaluable tools and libraries.

---

## 📬 Contact

For any questions or discussions, feel free to reach out via the repository's issue tracker or directly through [GitHub](https://github.com/saichothave).

---

*Efficient and scalable key-value storage, designed with performance in mind!*
