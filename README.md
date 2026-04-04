<a id="readme-top"></a>
<div align="center">
  
  [![Contributors][contributors-shield]][contributors-url]
  [![Forks][forks-shield]][forks-url]
  [![Stargazers][stars-shield]][stars-url]
  [![Issues][issues-shield]][issues-url]
  [![MIT License][license-shield]][license-url]
  [![C][c-shield]][c-url]

  <br />
  <h3 align="center">myPreCompiler</h3>

  <p align="center">
    A custom C precompiler developed as a group project for the exam "Sistemi Operativi II" in Sapienza's Bachelor of Computer Science course.
    <br />
    <br />
    <a href="https://github.com/fthinker/myprecompiler/issues">Report a bug</a>
    ·
    <a href="https://github.com/fthinker/myprecompiler/issues">Request new features</a>
  </p>
</div>

## About The Project

**myPreCompiler** is a custom-built C precompiler designed from the ground up as an academic homework. This project is currently being developed for the *Sistemi Operativi II* (Operating Systems II) exam at Sapienza University of Rome, Bachelor of Computer Science.

The precompiler handles essential directives, parsing of both standard and user-declared variable types and variable validation, producing a final report of a given C source file that lists possible variable related errors.

## Getting Started

To get a local copy up and running, follow these steps.

### Prerequisites

This project strictly requires the **GNU Compiler Collection (GCC)** to compile and run. Ensure you have it installed on your system before proceeding.

### Installation

1. Clone the repo
  ```shell
  git clone https://github.com/fthinker/myprecompiler.git
  ```
2. Navigate to the project directory
  ```shell
  cd myprecompiler
  ```
3. Compile the project using GCC
  ```
  gcc src/*.c -o myPreCompiler
  ```
## Usage

Run the compiled executable to parse and test your C source files. The program requires an input C file and can optionally output to a file or print verbose statistics.

<br>

Read input and save the statistics to an output file
  ```shell
  ./myPreCompiler -i input_file.c -o output_file
  ```
<br>

Read input and print the statistics to stdout (verbose mode)
  ```shell
  ./myPreCompiler -vi input_file.c
  ```
<br>

Read input, save to an output file AND print to stdout (verbose mode)
  ```shell
  ./myPreCompiler -i input_file.c -o output_file -v
  ```

## Contributors

As a group project, contributors are limited to the existing team members. However, feedback and suggestions are always welcome and appreciated!

<a href="https://github.com/fthinker/myprecompiler/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=fthinker/myprecompiler" alt="Contributors list" />
</a>

## License

Distributed under the MIT License. See `LICENSE` for more information.

[contributors-shield]: https://img.shields.io/github/contributors/fthinker/myprecompiler.svg?style=for-the-badge
[contributors-url]: https://github.com/fthinker/myprecompiler/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/fthinker/myprecompiler.svg?style=for-the-badge
[forks-url]: https://github.com/fthinker/myprecompiler/network/members
[stars-shield]: https://img.shields.io/github/stars/fthinker/myprecompiler.svg?style=for-the-badge
[stars-url]: https://github.com/fthinker/myprecompiler/stargazers
[issues-shield]: https://img.shields.io/github/issues/fthinker/myprecompiler.svg?style=for-the-badge
[issues-url]: https://github.com/fthinker/myprecompiler/issues
[license-shield]: https://img.shields.io/github/license/fthinker/myprecompiler.svg?style=for-the-badge
[license-url]: https://github.com/fthinker/myprecompiler/blob/main/LICENSE
[c-shield]: https://img.shields.io/badge/LANGUAGE-C-00599C?style=for-the-badge
[c-url]: https://en.wikipedia.org/wiki/C_(programming_language)
