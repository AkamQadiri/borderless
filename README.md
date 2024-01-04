# borderless

## Introduction

**borderless** is a straightforward C++ application originally designed to address the lack of native alt-tabbing in [Call of Duty: Black Ops](https://en.wikipedia.org/wiki/Call_of_Duty:_Black_Ops), where forcing alt-tab when in fullscreen mode disconnects the game. The project allows users to remove the borders of a specified window, making it borderless and fullscreen. It provides a console-based interface for selecting the desired window. All of this is achieved with the assistance of the Windows API.

## Features

- **INI Configuration:** The project stores and reads settings from an INI file, eliminating the need to choose a window every time you launch the program.
  
- **Console UI:** You can select the desired window using the console UI.

- **Compatibility:** Originally designed for [Call of Duty: Black Ops](https://en.wikipedia.org/wiki/Call_of_Duty:_Black_Ops), the program is now adapted to work with any windowed program or game.

## Usage

1. **Run the Program/Game:**
   - Launch the program/game that you want to be in fullscreen borderless (Ensure the program/game is in windowed mode).

2. **Run the Application:**
   - Execute the compiled `borderless_release.exe`.

3. **Select the Desired Window:**
   - Choose the desired window from the list of windows.

4. **Done:**
   - The selected window should now be in fullscreen borderless!
   - The next time you start the application, it should read `borderless.ini` and launch the program for you automatically, making it fullscreen borderless!

## Building the Project

The project uses CMake for building. Follow these steps to build the application:

1. **Make build Directory:**
   - Create a directory named `build` at the root level of the repository.

2. **Compile:**
   - Open a terminal and navigate to the `build` directory.
   - Run `cmake ..` to generate the build files.
   - Run `cmake --build .` to compile the executables.

## License

This project is licensed under the [MIT License](LICENSE).