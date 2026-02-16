# Qt Open UI Chat

A C++ and QML based chat interface component and example application, designed to connect with AI servers like llama.cpp.

## Features

-   **Modern UI**: Clean, responsive chat interface inspired by Open Web UI.
-   **Theme Support**: Toggle between Light (default) and Dark modes.
-   **Server Integration**: Connects to OpenAI-compatible endpoints (e.g., llama.cpp server).
-   **Self-Contained**: Builds into a standalone executable with all dependencies deployed.

## Building from Source

### Prerequisites

-   **CMake** (3.16+)
-   **Qt 6.5+** (Core, Gui, Qml, Quick, Network, QuickControls2)
-   **Compiler**: MSVC (Windows) or GCC/Clang (Linux)
-   **Build Tool**: Ninja or Visual Studio

### Steps

1.  Clone the repository:
    ```bash
    git clone https://github.com/Biswajee/qt-open-ui-chat-components.git
    cd qt-open-ui-workspace
    ```

2.  Build using CMake:
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build . --config Release
    ```

3.  Run the application:
    -   **Windows**: `example\Release\qt-open-ui-chat.exe` (Dependencies are automatically deployed).
    -   **Linux**: `./example/qt-open-ui-chat`

## Setup Llama.cpp on Windows on Snapdragon

To use this tool with a local AI model on Windows on Arm (Snapdragon), follow these steps:

1.  **Download Llama.cpp**:
    -   Go to the [llama.cpp releases](https://github.com/ggerganov/llama.cpp/releases).
    -   Download the `llama-bxxxx-bin-win-arm64-*.zip` (ensure it matches your architecture, ARM64 for Snapdragon).
    -   Extract the zip file.

2.  **Download a Model**:
    -   Download a GGUF model file (e.g., from [Hugging Face](https://huggingface.co/models?search=gguf)).
    -   Example: `llama-2-7b-chat.Q4_K_M.gguf`.

3.  **Run the Server**:
    -   Open PowerShell or Command Prompt.
    -   Navigate to the extracted llama.cpp folder.
    -   Run the server command:
        ```powershell
        .\server.exe -m path\to\your\model.gguf --host 0.0.0.0 --port 8080
        ```
    -   The server should start and listen on `http://localhost:8080`.

4.  **Connect with Qt Open UI Chat**:
    -   Launch `qt-open-ui-chat`.
    -   In the "Connect to Server" screen, enter: `http://localhost:8080/v1/chat/completions`.
    -   Click "Connect".
    -   Start chatting!

## CI/CD and Packaging

This project includes a GitHub Actions workflow that builds and packages the application for Windows and Linux automatically on every push.

-   **Windows**: Generates an NSIS installer (`.exe`).
-   **Linux**: Generates a `.deb` package and tarball.
