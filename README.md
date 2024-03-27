# Qtool Optimization Algorithm Implementation

This project addresses the challenge of transforming real-world constraints into a format suitable for solving nonlinear optimization problems.

## Project Overview

Providing code or libraries to automate the process of idealizing and incorporating constraints into MMA-based optimization problems.

**Algorithm:** Method of Moving Asymptotes (MMA)


## Dependencies 

To compile the program, you will need the following libraries:

- **libnlopt**: A library for nonlinear optimization. You can find more information about it [here](https://github.com/stevengj/nlopt).
- **libmath**: Standard math library, often included in standard C libraries.

## Build

To compile the program using CMake, follow these steps:

1. **Install Dependencies**: Ensure that you have the necessary dependencies installed on your system. You can typically install these using your package manager.

2. **Generare build process**: In your project directory, where the `CMakeLists.txt` file is present run:

```sh
cd build
cmake ..
```

3. **Build**: Run make

```sh
# From the build directory
make
```

## Tools

A custom VTK writer is present to understand how to assemble unstructured mesh and results. Located at:

- tools/make_vtu.py
