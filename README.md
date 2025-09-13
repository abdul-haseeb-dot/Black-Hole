# Black Hole

A strategic two-player number placement game built with C++ and Raylib where players take turns placing sequential numbers in a hexagonal grid, aiming to achieve the lowest sum around the final black hole.

## Game Overview

Black Hole is a tactical number placement game that combines strategic thinking with risk management. Players alternate turns placing numbers from 1 to 10 in holes arranged in a triangular/hexagonal pattern. When only one hole remains, it becomes the "black hole," and the numbers in adjacent holes are summed for each player. The player with the **lower sum wins** - making this a game where strategic restraint often trumps aggressive play.

### Key Features
- **Two-Player Gameplay**: Alternating turns between Player 1 (Dark Blue) and Player 2 (Red)
- **Sequential Number Placement**: Numbers increase from 1-10, with each player placing the same number before advancing
- **Animated Black Hole**: Smooth animation when the final hole transforms into a black hole
- **Adjacent Sum Calculation**: Automatic scoring based on numbers surrounding the black hole
- **Clean Visual Interface**: Hexagonal grid layout with clear player indicators and hover effects
- **Multiple Game Screens**: Instructions, gameplay, and statistics screens

## How to Play

### Basic Rules
1. **Turn Structure**: Players alternate placing the current number (starting with 1)
2. **Number Progression**: After both players place the same number, it increases (1→2→3...→10)
3. **Grid Layout**: Holes are arranged in a triangular pattern (1, 2, 3, 4, 5, 6 holes per row)
4. **Black Hole Creation**: When only one hole remains empty, it automatically becomes the black hole
5. **Scoring**: Numbers in holes adjacent to the black hole are summed for each player
6. **Victory Condition**: The player with the **lower adjacent sum wins**

### Gameplay Flow
1. **Instructions Screen**: Learn the rules and click to continue

  <img width="1098" height="597" alt="image" src="https://github.com/user-attachments/assets/347ad477-4c62-4a2d-b355-b41d2feb7124" />

2. **Game Screen**: 
   - Current player is displayed at the top
   - Hover over empty holes to see placement preview
   - Click on an empty hole to place your number
   - Watch the black hole animation when the game ends

  <img width="1098" height="597" alt="image" src="https://github.com/user-attachments/assets/053a5dda-ff1c-47a8-882d-36a517ce2f97" />
     
3. **Statistics Screen**: View final scores and winner declaration

  <img width="1098" height="597" alt="image" src="https://github.com/user-attachments/assets/8c5c6c1f-e4a1-4fd9-ad62-44b59af2bf70" />

### Strategic Considerations
- **Positional Awareness**: Consider where the black hole might appear
- **Risk Management**: Higher numbers create bigger risks if placed near potential black holes
- **Opponent Prediction**: Try to influence where your opponent places high-value numbers
- **Endgame Planning**: The final few placements often determine the winner

## Project Structure

```
BlackHole/
├── .gitignore                  # Git ignore rules for build files and OS artifacts
├── Makefile                    # Build configuration and compilation rules
├── README.md                   # Project documentation
├── header/                     # Header files (.hpp)
│   ├── Constants.hpp           # Game constants and configuration values
│   ├── Hole.hpp                # Hole structure and game state management
│   └── Screens.hpp             # Screen enumeration for game states
├── main/                       # Main application files
│   └── Main.cpp                # Entry point, game loop, and UI rendering
├── source/                     # Implementation files (.cpp)
│   └── Hole.cpp                # Hole functionality and game logic implementation
├── object/                     # Compiled object files (created during build)
└── game/                       # Final executable output directory
    └── BlackHole.exe           # Compiled game executable
```

### File Descriptions

#### Header Files (`header/`)
- **Constants.hpp**: Screen dimensions, hole radius, colors, animation settings, and visual constants
- **Hole.hpp**: Hole structure definition, global game state variables, and function declarations
- **Screens.hpp**: Enumeration for different game screens (INSTRUCTIONS, GAME, STATISTICS)

#### Source Files (`source/`)
- **Hole.cpp**: 
  - Hole rendering with hover effects and black hole animation
  - Click detection and number placement logic
  - Black hole creation and adjacent sum calculation
  - Animation update system for smooth transitions

#### Main Application (`main/`)
- **Main.cpp**: 
  - Game initialization and main loop
  - Screen management (instructions, gameplay, statistics)
  - Hexagonal hole grid generation and positioning
  - User interface rendering and event handling
  - Game flow control and state transitions

## Installation & Setup

### Prerequisites
1. Install a C++ compiler (e.g., GCC or MinGW for Windows)
2. Install [Raylib](https://www.raylib.com/) - a simple and easy-to-use library for game development
3. Ensure you have a terminal or command prompt to run commands

### Building the Game
1. Clone or download the project
2. Navigate to project directory
3. Run the following command to compile the game:
```bash
make all
```
4. Or use this command to compile and run the game in one step:
```bash
make run
```

### Cleaning Build Files
To remove compiled files and clean the project, run:
```bash
make clean
```

## Technical Details

### Dependencies
- **Raylib**: Cross-platform game development library for graphics and input
- **C++17**: Modern C++ standard for enhanced features and performance
- **Standard Library**: Vector containers for grid management and string utilities

### Build System
- **Makefile**: Automated compilation with dependency management
- **Object Files**: Separate compilation for faster incremental builds
- **Static Linking**: Self-contained executable with embedded libraries

### Architecture
- **Global State Management**: Centralized game variables for turn management and animations
- **Modular Design**: Separate classes for game entities (Hole) and screen management
- **Event-Driven Input**: Mouse-based interaction with hover preview and click detection
- **Animation System**: Time-based animations for smooth black hole transformation

### Key Algorithms
- **Hexagonal Grid Generation**: Mathematical positioning of holes in triangular pattern
- **Adjacent Sum Calculation**: Six-directional neighbor checking for scoring
- **Collision Detection**: Precise circular hit detection for hole selection
- **Animation Interpolation**: Linear progression for black hole fill animation

### Visual Features
- **Hover Effects**: Dynamic ring highlighting for interactive feedback
- **Player Color Coding**: Consistent color scheme throughout the game
- **Smooth Animations**: Timed black hole formation with visual feedback
- **Responsive UI**: Screen-centered layouts that adapt to different elements

## Game Statistics & Scoring

### Adjacency Pattern
The black hole checks six adjacent positions in a hexagonal pattern:
- Top-left, Top-right
- Left, Right  
- Bottom-left, Bottom-right

### Scoring System
- Only numbers placed by each player in holes adjacent to the black hole count toward their score
- Empty holes and the black hole itself don't contribute to scoring
- Lower total sum wins the game
- Ties result in a draw

## Future Improvements

- **Difficulty Levels**: AI opponent with adjustable strategy depth
- **Tournament Mode**: Best-of-series gameplay with match tracking
- **Move Timer**: Add time pressure with per-turn or total game timers
- **Online Multiplayer**: Network play with matchmaking and lobbies
- **Custom Grid Sizes**: Variable hole counts for different game lengths and complexity
