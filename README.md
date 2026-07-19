# URS Seminar
Seminarski zadatak za kolegij Ugradbenih Računalnih sustava

## Docker dev container workflow

Project now includes a standalone development container in `.devcontainer/` with:

- ARM GNU toolchain (`arm-none-eabi-gcc`, `arm-none-eabi-gdb`)
- CMake + Ninja build tools
- OpenOCD + ST-Link tools for flashing and debugging
- VS Code extension recommendations for CMake and Cortex debug

### Quick start

1. Open project in VS Code.
2. Run command: `Dev Containers: Reopen in Container`.
3. Build with preset `Debug`.

### Flash and debug inside container

- Flash task: `OpenOCD: Flash project (SWD)`
- Combined task: `Build + Flash (OpenOCD)`
- Debug launch: `Build & Debug Microcontroller - OpenOCD (Container)`

This repository is configured for container-native flashing and debugging only.
