# Backgammon Game

```
     ____    _    ____ _  ______    _    __  __ __  __  ___  _   _ 
    | __ )  / \  / ___| |/ / ___|  / \  |  \/  |  \/  |/ _ \| \ | |
    |  _ \ / _ \| |   | ' / |  _  / _ \ | |\/| | |\/| | | | |  \| |
    | |_) / ___ \ |___| . \ |_| |/ ___ \| |  | | |  | | |_| | |\  |
    |____/_/   \_\____|_|\_\____/_/   \_\_|  |_|_|  |_|\___/|_| \_|
```

## Overview

This is a rewrite of a Backgammon game originally built for a university project in 2023. The original version worked, but it was written procedurally without much structure.

This version is completely rewritten with a proper object-oriented architecture. The code is now actually maintainable and extensible. Adding new features, fixing things, or implementing AI strategies doesn't require diving into spaghetti code.

---

## Features

- Interactive gameplay: play as a human against a simple AI
- Proper backgammon rules: piece movement, capturing opponent pieces, re-entering from bar, doubles
- Game save/load (planned)
- Undo system (planned)
- ASCII board visualization in terminal

---

## Project Structure

```
backgammon/
├── Board.h / Board.cpp          # Game board representation
├── Player.h / Player.cpp        # Base player class
├── Real_player.h / Real_player.cpp    # Human player
├── rand_player.h / rand_player.cpp    # Random player (makes random moves)
├── AI_player.h / AI_player.cpp        # Advanced AI (planned)
├── Game.h / Game.cpp            # Game orchestration and rules
├── Utils.h / Utils.cpp          # Utility functions
└── backgammon.cpp               # Entry point and menu
```

### Architecture Highlights

- **Player Hierarchy**: Abstract `player` base class with concrete implementations (`real_player`, `rand_player`, `AI_player`). Easy to add new player types.
- **Board State Management**: The `board` class encapsulates all game state and provides methods for legal move validation.
- **Move Generation**: Generic `getallpossiblemoves()` ensures consistent move logic for all player types.
- **Separation of Concerns**: Gameplay logic, UI rendering, and input handling are cleanly separated.

---

## Build & Run

### Requirements

- **C++17** or later
- **Visual Studio 2022+** or compatible compiler (tested with MSVC)
- **Windows** (for VT100 terminal support in current implementation)

### Building

```bash
# Using Visual Studio
# Open backgammon.vcxproj and build (Ctrl+Shift+B)

# Or from command line (with MSVC)
msbuild backgammon.vcxproj
```

### Running

```bash
./backgammon.exe
```

You'll see the main menu:
```
                     press 1 to load from file
                     press 2 to start new game
```

---

## How to Play

1. **Start a new game** (option 2) — you play as Black (B)
2. **View the board**:
   ```
   13 14 15 16 17 18  | BAR |  19 20 21 22 23 24
   ... (top half)
   ─────────────────────────────────────
   ... (bottom half)
    12 11 10  9  8  7 | BAR |   6  5  4  3  2  1
   ```
3. **Choose your move** from the available options (each option shows `from -> to`)
4. **Moves are automatically validated** — illegal moves are filtered out
5. **Game continues** until one player bears off all pieces

---

## Game Rules Implemented

- Standard backgammon movement and capturing
- Bearing off pieces
- Re-entering from the bar
- Doubles (4 moves instead of 2)
- Legal move validation

---

## Future Improvements

- Game save/load to file
- Undo history
- Better AI player
- Settings (colors, difficulty, etc.)
- Tests

---

## Code Quality

The rewrite uses proper OOP practices, modern C++ patterns, and a clean separation of concerns. Adding new player types or modifying game rules is straightforward because the code is structured for it.

---

## Contributing

Want to add something? The code is structured to make it easy:

- **New player type**: Create a class that inherits from `player` and override `makemove()`
- **Change game rules**: Modify `board::canLand()` or `board::executeMove()`
- **Improve the UI**: Update `board::draw()`

