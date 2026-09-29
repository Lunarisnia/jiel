# jiel

Portable C++23/OpenGL starter project for Windows and macOS. CMake downloads
SDL3, GLAD, and fmt during configuration; only CMake, Git, a C++ compiler, and
an internet connection are required for the first build.

## Build

Ninja (Windows or macOS):

```sh
cmake --preset debug
cmake --build --preset debug
```

Configure, build, and run the sandbox in one command:

```sh
make run
```

Use `make run CONFIG=Release` for a release build. The same command is exposed
in Zed as the `Run Sandbox` task.

Visual Studio 2022:

```sh
cmake --preset windows-msvc
cmake --build --preset windows-msvc-debug
```

The executable is under `build/<preset>/apps/sandbox`. With a multi-config
generator such as Visual Studio, it is in the `Debug` or `Release` subfolder.

## Add a dependency

Declare and fetch it in `cmake/Dependencies.cmake`, then add its imported target
to `target_link_libraries` in the target that uses it. Keeping dependencies and
target wiring separate makes platform changes local and avoids global include
or linker settings.
