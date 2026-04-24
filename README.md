# Stellar Survival 🚀
> "Defeat them! Outwit them! Survive!"

## 📖 Project Overview
**Stellar Survival** is a real-time, console-based action-adventure game built entirely in C++. Set in the year 2147, you play as the last survivor of a reconnaissance mission stranded on a hostile alien planet. To escape, you must navigate a labyrinth, survive deadly laser traps, defeat the alien forces, and reach the extraction spaceship before your health runs out.

This project was built to explore core computer science concepts—specifically how to build a non-blocking game loop, optimize multi-entity collision detection, and manage dynamic states in memory without an external game engine.

## 🎮 Game Controls & Navigation
The game utilizes asynchronous keyboard inputs for real-time movement and combat:
* **Arrow Keys (↑ ↓ ← →):** Move the player through the maze.
* **V:** Aim gun to the left.
* **B:** Aim gun to the right.
* **Spacebar:** Fire bullets.

## 📜 Instructions & Gameplay Rules
1. **Objective:** Defeat at least 10 enemies and safely reach the spaceship to win the game. The spaceship spawns randomly in the top areas of the maze.
2. **Combat:** Shoot bullets at enemies to defeat them. There are three tiers of enemies (Unarmed, Armed, and Boss/AlienX) distributed throughout the maze.
3. **Health & Lives:** * Your player starts with **100 Health** and **5 Lives**.
   * Health reduces by 1 when hit by a static laser trap or an enemy bullet.
   * When health reaches 0, you lose 1 Life. If your lives reach 0, it's Game Over.
4. **Progression:** Destroy enemies or evade them to progress. You must secure the required 10 kill count before boarding the spaceship.

## 🎧 Audio & Immersion
Stellar Survival doesn't just rely on visuals. The game features programmatic, frequency-based sound effects built using the Windows API, including:
* Typewriter-effect storytelling synced with Morse code beeps.
* High-frequency laser fire audio.
* Dramatic suspense drops and explosion sound effects during combat.

## 🧠 Core Engineering Concepts
* **Parallel Arrays for State Management:** Tracked the Cartesian coordinates (`x`, `y`), directional states, and health of up to 11 enemies and hundreds of active projectiles simultaneously without object-heavy overhead.
* **Non-Blocking Game Loop:** Replaced inefficient nested loops with flattened array traversal, allowing the game to listen for user input (`GetAsyncKeyState`) while continuously rendering moving entities and checking collisions in O(n) time.
* **Dynamic Pointer Tracking:** Managed player movement dynamically in memory using C++ pointers to ensure rapid state updates and zero rendering lag.

## 💻 Tech Stack
* **Language:** C++ 
* **Libraries:** `<iostream>`, `<windows.h>`, `<conio.h>`, `<random>`
* **Architecture:** Procedural/Modular Programming

## ⚙️ Installation & Setup
1. **Clone the repository:**
   ```bash
   git clone [https://github.com/aatikayousuf/Stellar-Survival.git]
