<div align="center">

<h1>♜ &nbsp; The GrandMaster's Gambit &nbsp; ♖</h1>

<p>
  <img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=16&pause=1000&color=8CC4FF&center=true&vCenter=true&width=520&lines=Two-Player+Chess+in+C%2B%2B+%2B+SFML;Object-Oriented+Design;Click+to+Select.+Click+to+Move.+Checkmate." alt="Typing SVG" />
</p>

**A fully featured two-player chess game built in C++ with SFML graphics.**

![C++](https://img.shields.io/badge/C++-17-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-2.x-8CC445?style=flat-square&logo=sfml&logoColor=white)
![OOP](https://img.shields.io/badge/Paradigm-OOP-blueviolet?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-yellow?style=flat-square)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=flat-square)

</div>

---

## ♟ Overview

**The GrandMaster's Gambit** is a complete, graphical two-player chess game developed as a final project for the Object-Oriented Programming Lab at **FAST National University, CFD Campus**. The game features a polished SFML window with interactive piece selection, valid move highlighting, real-time player stats, and automatic match record saving.

---

## ✦ Features

| Feature | Details |
|---|---|
| 🖱️ **Click-to-Move** | Select a piece, see valid moves highlighted, click to move |
| 🟡 **Move Highlighting** | Selected piece glows; valid squares marked with grey dots |
| 📊 **Live Sidebar** | Player names, color, captured piece count, active turn |
| 🏆 **Win Detection** | Automatic game result detection |
| 💾 **Match Records** | Game saved to file with date, players, result, full move history |
| ♟ **All 6 Piece Types** | Pawn, Knight, Bishop, Rook, Queen, King — all with correct movement |

---



---

## 🗂️ Project Structure

```
The-GrandMasters-Gambit/
│
├── 📄 Piece.h / Piece.cpp          ← Abstract base class for all pieces
├── 📄 Pawn.h / Pawn.cpp            ← Pawn movement logic
├── 📄 Knight.h / Knight.cpp        ← L-shaped knight movement
├── 📄 Bishop.h / Bishop.cpp        ← Diagonal bishop movement
├── 📄 Queen.h / Queen.cpp          ← Combined rook + bishop movement
├── 📄 King.h / King.cpp            ← King movement & check support
├── 📄 Player.h / Player.cpp        ← Player name, color, captured count
├── 📄 Board.h / Board.cpp          ← 8×8 grid, piece placement, moves
├── 📄 Game.h / Game.cpp            ← Game loop, SFML rendering, file I/O
├── 📄 Renderer.h / Renderer.cpp    ← SFML draw calls: board, pieces, UI
├── 📄 Types.h                      ← Shared enums: Color, PiecesType
│
└── 📁 assets/pieces/               ← PNG sprites (12 piece images)
```

---

## 🧠 OOP Design

The project is built around a clean inheritance hierarchy rooted at an abstract `Piece` base class.

```
                    ┌─────────────────┐
                    │     Piece       │  ← Abstract Base Class
                    │─────────────────│
                    │ - color         │
                    │ - type          │
                    │ - HasMoved      │
                    │─────────────────│
                    │ + getColor()    │
                    │ + getType()     │
                    │ + getSymbol()   │  ← virtual
                    │ + ~Piece()      │  ← virtual destructor
                    └────────┬────────┘
                             │
        ┌──────┬─────────────┼────────────┬────────┬───────┐
        ▼      ▼             ▼            ▼        ▼       ▼
      Pawn   Knight        Bishop        Rook    Queen    King
```

### Core OOP Concepts Used

**Encapsulation** — All data members in `Piece` and `Player` are private, exposed only via getter/setter methods.

**Inheritance** — All 6 piece types inherit from `Piece`, reusing color, type, and move-tracking logic.

**Polymorphism** — The `Board` stores `Piece*` pointers. `getSymbol()` and move validation dispatch to the correct derived class at runtime.

**Abstraction** — The `Game` and `Board` classes interact with pieces through the `Piece` interface, with no knowledge of concrete types.

**Operator Overloading** — `operator<<` is overloaded on `Piece` for clean stream output.

---

## 💾 File Handling — Match Records

After every completed game, a match record is automatically saved:

```
DATE: 2026-05-02
WHITE: Ali
BLACK: Hashim
RESULT: White Wins
d2d4 d7d5 e2e4 d5e4 c2c4 b8c6 b1c3 c6d4 c3e4 d4e2 d1d8 e8d8
c4c5 e2g1 h1g1 g7g5 e4g5 e7e6 g5f7 d8d7 f7h8 g8f6 c1h6 ...
```

Each move is stored in algebraic notation (`d2d4` = from d2 to d4), preserving the full game history.

---

## ⚙️ Build & Run

### Prerequisites
- C++17 compiler (MSVC / GCC / Clang)
- [SFML 2.x](https://www.sfml-dev.org/download.php) installed

### Compile (Linux / MinGW)

```bash
g++ -std=c++17 *.cpp -o chess -lsfml-graphics -lsfml-window -lsfml-system
./chess
```

### Compile (Visual Studio)
1. Add all `.cpp` files to the project
2. Link SFML libraries in project properties
3. Build and run

### Controls

| Input | Action |
|---|---|
| `Left Click` (once) | Select a piece |
| `Left Click` (again) | Move to highlighted square |
| `ESC` | Quit the game |

---

## 👥 Team

<div align="center">

| | Developer | Roll No | Contributions |
|:---:|---|---|---|
| ♟ | **Ali Hassan** | 25F-0644 | Piece class hierarchy (all 6 types), Player class, File handling, Operator overloading |
| ♔ | **Hashim Nagi** | 25F-0685 | Board class, Game loop, SFML rendering, Renderer class, Types.h, Asset management |

</div>

---

## 📚 Course Info

> **Object-Oriented Programming Lab — Final Project**
> FAST National University, CFD Campus
> Semester: Spring 2026

---

<div align="center">

*"Every chess master was once a beginner."*

**⭐ Star this repo if you enjoyed it!**

</div>
