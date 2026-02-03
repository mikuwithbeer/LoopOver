## LoopOver

![License](https://img.shields.io/badge/license-MIT-red.svg)
![Platform](https://img.shields.io/badge/platform-macOS-green.svg)
![Language](https://img.shields.io/badge/language-C-blue.svg)


> [!CAUTION]
> **Disclaimer**
>
> This software is for educational purposes only.
> The author assumes **no responsibility** for misuse.
> Please support the developers by purchasing a genuine license.
> Software development relies on financial support from users.


LoopOver is a lightweight CLI utility designed to reset the evaluation period for CrossOver on macOS.
It programmatically modifies the application's property list to update the "first run" date,
thus refreshing the trial cycle.

---

### Prerequisites

To run LoopOver, ensure your environment meets the following criteria:

- **OS**: macOS `v10.15` (Catalina) or later.
- **Target**: CrossOver must be installed in its default location.

### Usage

You can download the pre-built binary from the latest successful run in
the [Actions](https://github.com/mikuwithbeer/LoopOver/actions) tab.

Mark the binary as executable and move it to your `/usr/local/bin` directory:

```bash
chmod +x LoopOver
sudo mv LoopOver /usr/local/bin
```

You can run from the command line whenever your trial period expires:

```bash
LoopOver
```

Due to macOS security restrictions, you might need to give the binary permission to proceed.

### Building

If you prefer to build from source rather than using the pre-compiled binary, you will need a C compiler and CMake.

- **Compiler**: C23 compliant compiler (`clang` is recommended).
- **CMake**: CMake `v4.2` or later.

Then you can build the project using CMake like any other project.

### License

This project is licensed under the MIT license.
