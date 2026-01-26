## LoopOver

![License](https://img.shields.io/badge/license-MIT-red.svg)
![Platform](https://img.shields.io/badge/platform-macOS-green.svg)
![Language](https://img.shields.io/badge/language-C-blue.svg)


> [!CAUTION]
> **Disclaimer**
>
> This software is for educational purposes only. The author assumes **no responsibility** for misuse. Please support
> the developers by purchasing a genuine license.


LoopOver is a lightweight CLI utility designed to reset the evaluation period for CrossOver on macOS.
It programmatically modifies the application's property list to update the "first run" date,
thus refreshing the trial cycle.

---

### Requirements

- macOS `v10.15` or later.
- CrossOver must be installed in its default location.
- Building the project since pre-built binaries will not be released.
    - C23 (using `clang` as preferred compiler).
    - CMake `v4.2` or later.

### Usage

After compiling the project and getting the binary, you can run the executable
whenever your trial expires.

### License

This project is licensed under the MIT license.
