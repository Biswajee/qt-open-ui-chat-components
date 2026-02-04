# Qt Open UI Chat Example

A modern, responsive chat UI component (`ChatFrame`) styled like open-web-ui, built with Qt 6 and QML.  
Includes a reusable UI library and an example application.

## Features

- **QML-based**: Modern, responsive, and easily styled.
- **Open-web-ui look**: Rounded corners, shadows, dark theme, and spacing.
- **Modular**: UI library (`ChatUI` module) and example app.
- **Qt6 only**: No Qt5 compatibility.

## Project Structure

```
qt-open-ui/
├── CMakeLists.txt
├── ui/
│   ├── CMakeLists.txt
│   └── ChatFrame.qml
├── example/
│   ├── CMakeLists.txt
│   ├── main.cpp
│   └── Main.qml
└── README.md
```

## Build Instructions

### Prerequisites

- Qt 6.x (with QML, Quick, and Quick Controls modules)
- CMake 3.16+
- C++17 compiler

### Build

```sh
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

### Run

The built executable and required DLLs will be in:
- `__Builds/x64/Debug/bin` or
- `__Builds/x64/Release/bin`

Run `chat_example.exe` from the appropriate `bin` directory.

> **Tip:** If you see missing DLL or QML module errors, run [`windeployqt`](https://doc.qt.io/qt-6/windows-deployment.html#windeployqt) on the executable.

## Usage

- The `ChatFrame` component is available as a QML module:  
  `import ChatUI 1.0`
- See `example/Main.qml` for usage.

## License

MIT License (add your license here)