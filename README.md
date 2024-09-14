# MiniTalk Project

MiniTalk is a simple inter-process communication (IPC) system that allows processes to send and receive messages using UNIX signals.

## How to Run

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/minitalk.git
   cd minitalk
   ```

2. Compile the code:
   ```
   make
   ```

3. Start the server:
   ```
   ./server
   ```

4. Send a message from the client:
   ```
   ./client <server_pid> "Your message here"
   ```

Replace `<server_pid>` with the PID displayed by the server.
