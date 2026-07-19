# Dev Container Notes

This project can be developed and debugged fully from the container.

## Build inside container

Use CMake preset `Debug`:

- Configure: `cmake --preset Debug`
- Build: `cmake --build --preset Debug`

## Flash/debug with Nucleo ST-Link

This container uses OpenOCD with ST-Link.

- Flash task: `OpenOCD: Flash project (SWD)`
- Debug launch: `Build & Debug Microcontroller - OpenOCD (Container)`

## USB access notes

- Container expects direct USB access to ST-Link for OpenOCD.
