# Falling Blocks Game

This is a simple game built using **SFML** (Simple and Fast Multimedia Library) in C++. The game involves avoiding or collecting falling blocks of different colors. Each block type has a different score value, and the game ends when your health reaches zero.

## Features
- Dynamic falling blocks with randomized colors and sizes.
- Points system based on block type.
- Level progression with increasing block speed.
- Game-over screen when health reaches zero.
  
## Prerequisites
- **SFML**: Download and set up SFML for your version of Visual Studio from [SFML Downloads](https://www.sfml-dev.org/download.php).
- **Visual Studio**: Recommended version Visual Studio 2019 or later.
  
## Project Setup

1. **Download and Extract SFML**: 
   - Download SFML from [SFML Downloads](https://www.sfml-dev.org/download.php).
   - Extract it to a location on your computer.

2. **Configure Visual Studio Project**:
   - Go to **Project Properties** → **Configuration Properties** → **VC++ Directories**.
   - Add paths for **Include Directories** and **Library Directories**:
     - **Include Directory**: `[Path to SFML]/include`
     - **Library Directory**: `[Path to SFML]/lib`

3. **Link SFML Libraries**:
   - Under **Linker** → **Input** in Project Properties, add the following libraries to **Additional Dependencies**:
     ```
     sfml-graphics.lib
     sfml-window.lib
     sfml-system.lib
     ```
   - For the Debug configuration, link with the `-d` versions of each library, such as `sfml-graphics-d.lib`, etc.

4. **Copy DLLs**:
   - Copy the necessary `.dll` files from `[Path to SFML]/bin` to your project’s Debug/Release directory. For example:
     - `sfml-graphics.dll`
     - `sfml-window.dll`
     - `sfml-system.dll`
   - For Debug mode, use the `-d` versions, like `sfml-graphics-d.dll`, etc.

## Usage
After setting up the project, you can build and run it within Visual Studio. 

### Controls
- Use the mouse to click on blocks to collect them and gain points.
- The game displays a game-over screen when your health reaches zero.

## Project Structure

```plaintext
Falling Blocks Game/
├── src/
│   ├── Game.cpp
│   ├── Game.h
│   └── main.cpp
├── include/
│   └── SFML headers and project headers
└── resources/
    ├── fonts/
    │   └── KnightWarrior.otf
