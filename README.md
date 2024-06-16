# Maze Project

A C-based maze game utilizing SDL2 and raycasting techniques for rendering a pseudo-3D environment. This project features player navigation, collision detection, and dynamic maze generation.

## Features

- **Pseudo-3D Rendering:** Uses raycasting to create a first-person view of the maze.
- **Player Navigation:** Move through the maze using keyboard controls.
- **Collision Detection:** Prevents the player from walking through walls.
- **Dynamic Maze Generation:** Procedurally generated mazes for endless gameplay.

## Requirements

- C Compiler (e.g., gcc flags: `-Wall -Werror -Wextra -pedantic`)
- Source files are in `src` directory, headers in `inc`
- Code is Betty style compliant
- SDL2 Library

## Installation

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/yourusername/maze-project.git
    cd maze-project
    ```

2. **Install SDL2:**

    - **Linux:**

      ```bash
      sudo apt-get install libsdl2-dev
      ```

    - **macOS:**

      ```bash
      brew install sdl2
      ```

    - **Windows:**
      - Download SDL2 from [SDL2 Downloads](https://www.libsdl.org/download-2.0.php)
      - Follow the instructions for setting up SDL2 in your development environment.

3. **Build the Project:**

    ```bash
    make
    ```

4. **Run the Project:**

    ```bash
    ./maze_project
    ```

## Usage

- **W**: Move forward
- **S**: Move backward
- **A**: Turn left
- **D**: Turn right
- **Arrow Keys**: Rotate camera
- **Additional Controls**: Enable/disable map view, start/stop rain, etc.

## Features

1. **Walls:** Create a window with SDL2 and use raycasting to draw walls.
2. **Orientation:** Draw walls in different colors based on orientation (NORTH/SOUTH vs EAST/WEST).
3. **Rotation:** Rotate the camera using keyboard or mouse inputs.
4. **Move:** Move the player using keyboard inputs.
5. **Collision Detection:** Prevent the player from entering walls.
6. **Parser:** Implement a parser to load the map from a file.
7. **Draw the Map:** Draw the map on the window, including the player's line of sight.
8. **Textures:** Add textures to walls.
9. **Multi-tasking:** Handle multiple events simultaneously (e.g., move and rotate).
10. **Ground Textures:** Add textures to the ground and/or ceiling.
11. **Weapons:** Add weapon textures.
12. **Enemies:** Add enemies to the game.
13. **Weather Effects:** Add rain with the ability to start/stop it.
14. **Extra Options:** Shadows, special lighting, and more creative features.

## Contributing

1. Fork the repository
2. Create a new branch (`git checkout -b feature-branch`)
3. Commit your changes (`git commit -am 'Add new feature'`)
4. Push to the branch (`git push origin feature-branch`)
5. Create a new Pull Request

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgements

- SDL2 Library: [SDL2](https://www.libsdl.org/)
- Raycasting technique inspired by [Lode Vandevenne's tutorial](https://lodev.org/cgtutor/raycasting.html)
