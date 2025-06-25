# Audio File Transfer via Socket Programming

This project provides a simple C implementation for transferring audio files over TCP sockets. It demonstrates core network programming concepts: socket creation, connection handling, streaming binary data in chunks, and basic error checking.

## 🔑 Key Features

* **Reliable TCP Transfer:** Ensures ordered, lossless delivery of audio data.
* **Chunked Streaming:** Sends and receives data in configurable 1024‑byte blocks to balance performance and memory use.
* **Minimal Protocol:** Establishes a connection, streams file contents, and closes gracefully—no external dependencies.
* **Cross‑Platform Ready:** POSIX sockets on Linux/macOS; easily adaptable to Winsock for Windows.

## 📂 Project Files

* **server.c** — Listens on port 9999, reads `audioFile.mp3`, and streams it to clients.
* **client.c** — Connects to a server, receives the file stream, and writes it as `recvAudio.mp3`.
* **audioFile.mp3** — Sample audio file for demonstration.
* **client** / **server** — Precompiled executables (optional).

## ⚙️ Prerequisites

* GCC or any C compiler with C99 support.
* POSIX‑compliant environment (Linux/macOS) or Winsock set up on Windows.

## 🚀 Build & Run

1. **Compile:**

   ```bash
   gcc -o server server.c
   gcc -o client client.c
   ```
2. **Run the server:**

   ```bash
   ./server
   ```
3. **Run the client (in another terminal or machine):**

   ```bash
   ./client <server_ip>
   ```
4. **Result:**

   * Server logs connection details and confirms file sent.
   * Client saves the received stream as `recvAudio.mp3` in its working directory.

## 🔍 How It Works

1. **Server** binds to port 9999, listens, and accepts incoming connections.
2. **Client** establishes a TCP connection to the server’s IP and port.
3. **Server** opens `audioFile.mp3`, reads 1024-byte chunks, and sends them over the socket until EOF.
4. **Client** reads incoming bytes in 1024-byte blocks and writes them to `recvAudio.mp3`.
5. Both sides close the connection once transfer completes.
