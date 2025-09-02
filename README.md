# Hekla - OpenGL C++20 Project

A modern OpenGL project template using GLFW for window management, GLAD for OpenGL function loading, and CMake for build configuration. This project is set up with C++20 standards and follows clean code practices.

## Features

- 🚀 **Modern C++20** - Uses the latest C++ standard features
- 🎮 **GLFW 3.3.8** - Cross-platform window and input handling (via git submodules)
- ⚡ **GLAD** - OpenGL function loader for OpenGL 3.3 Core Profile
- 🔧 **CMake** - Modern build system with git submodule integration
- 🧹 **Clean Architecture** - Organized project structure following best practices

## Project Structure

```
hekla/
├── CMakeLists.txt          # Main CMake configuration
├── README.md               # This file
├── LICENSE                 # License file
├── .gitmodules            # Git submodules configuration
├── src/                    # Source files
│   └── main.cpp           # Main application entry point
├── include/               # Header files (for your custom headers)
├── extern/                # External libraries
│   ├── glfw/              # GLFW submodule (git submodule)
│   └── glad/              # GLAD OpenGL loader
│       ├── include/       # GLAD headers
│       │   ├── glad/
│       │   └── KHR/
│       └── src/           # GLAD implementation
└── build/                 # Build directory (created during build)
```

## Prerequisites

- **CMake 3.20+** - [Download CMake](https://cmake.org/download/)
- **C++20 compatible compiler**:
  - GCC 10+ / Clang 10+ / MSVC 2019+
- **Git** - For cloning dependencies
- **OpenGL 3.3+ support** - Modern graphics drivers

### Linux Additional Dependencies

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install build-essential cmake git libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev

# Fedora/CentOS/RHEL
sudo dnf install gcc-c++ cmake git libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel mesa-libGL-devel

# Arch Linux
sudo pacman -S base-devel cmake git libx11 libxrandr libxinerama libxcursor libxi mesa
```

## Building

### Quick Start

```bash
# Clone the repository with submodules
git clone --recursive <your-repo-url>
cd hekla

# If you already cloned without --recursive, initialize submodules:
# git submodule update --init --recursive

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build the project
cmake --build .

# Run the executable
./bin/Hekla  # Linux/macOS
# or
.\bin\Hekla.exe  # Windows
```

### Build Configuration Options

```bash
# Debug build (default)
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build
cmake -DCMAKE_BUILD_TYPE=Release ..

# Specify compiler (if needed)
cmake -DCMAKE_CXX_COMPILER=g++ ..
```

### IDE Integration

#### Visual Studio Code
1. Install the CMake Tools extension
2. Open the project folder
3. Use `Ctrl+Shift+P` → "CMake: Configure"
4. Use `Ctrl+Shift+P` → "CMake: Build"

#### CLion
1. Open the project folder
2. CLion will automatically detect CMakeLists.txt
3. Build using the IDE's build system

#### Visual Studio 2019/2022
1. File → Open → CMake...
2. Select CMakeLists.txt
3. Build using the IDE

## What's Included

### GLFW Features
- Cross-platform window creation
- Input handling (keyboard, mouse)
- OpenGL context management
- Monitor and video mode queries

### GLAD Features
- OpenGL 3.3 Core Profile function loading
- Cross-platform OpenGL function resolution
- Runtime OpenGL feature detection

### Project Features
- Basic OpenGL window with clear color
- Input handling (ESC to close)
- Window resize handling
- OpenGL version information display

## Usage

The main application creates a window that:
- Displays OpenGL version information in the console
- Shows a teal-colored clear screen
- Responds to ESC key to close
- Handles window resizing

Extend the `main.cpp` file to add your own OpenGL rendering code.

## Troubleshooting

### Common Issues

**CMake not found**
```bash
# Install CMake from https://cmake.org/download/
# Or use package manager (see Prerequisites)
```

**GLFW compilation errors**
- Ensure you have the required system libraries installed
- Check that your compiler supports C++20

**OpenGL context creation fails**
- Update your graphics drivers
- Ensure your system supports OpenGL 3.3+

**Library linking errors on Linux**
```bash
# Install missing development packages
sudo apt-get install libgl1-mesa-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
```

**Git submodule issues**
```bash
# If you get "Git submodules not initialized" error:
git submodule update --init --recursive

# If submodule seems outdated:
git submodule update --remote

# Check submodule status:
git submodule status
```

## Development

### Adding New Source Files
1. Add `.cpp` files to the `src/` directory
2. Add `.h/.hpp` files to the `include/` directory
3. CMake will automatically detect and compile them

### Adding Dependencies
1. **Git Submodules** - For libraries you want to pin and potentially modify:
   ```bash
   git submodule add https://github.com/user/library.git extern/library
   # Then add `add_subdirectory(extern/library)` to CMakeLists.txt
   ```
2. **CMake FetchContent** - For libraries you just want to use:
   ```cmake
   FetchContent_Declare(library GIT_REPOSITORY https://github.com/user/library.git)
   FetchContent_MakeAvailable(library)
   ```
3. **System packages** - For system-installed libraries via find_package()

## Contributing

1. Follow the existing code style
2. Use meaningful commit messages
3. Add documentation for new features
4. Test on multiple platforms when possible

## License

[Specify your license here]

## Resources

- [LearnOpenGL](https://learnopengl.com/) - Excellent OpenGL tutorials
- [GLFW Documentation](https://www.glfw.org/docs/latest/)
- [GLAD Web Service](https://glad.dav1d.de/) - Generate OpenGL loaders
- [CMake Documentation](https://cmake.org/documentation/)
