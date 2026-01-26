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
- (Optional) To build yourself:
    - C23 (using `clang` as preferred compiler).
    - CMake `v4.2` or later.

### Usage

You can download the pre-built binary from the latest successful run in
the [Actions](https://github.com/mikuwithbeer/LoopOver/actions) tab.

After getting the binary, run the executable whenever your trial expires.

### License

This project is licensed under the MIT license.
