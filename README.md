# Stellar Survival 🚀

> An action-packed, console-based survival game engineered from first principles in C++. 

## 📖 Project Overview
**Stellar Survival** is a dynamic maze-navigation game where the player must survive an alien planet. The objective is to navigate a labyrinth, defeat at least 10 hostile aliens, evade static laser traps, and reach a randomly spawned extraction spaceship to win. 

This project was developed as my final project for the **Programming Fundamentals (CSC-102)** course at the University of Engineering and Technology (UET), Lahore. It was built entirely from scratch to demonstrate how core computer science concepts—like parallel arrays, pointers, and optimized loops—can be used to build a robust game engine within a standard Windows console.

## 🧠 The Engineering Behind the Game
Building a real-time game in a CLI environment presents significant performance challenges, specifically regarding rendering lag and input blocking. Here is how those were solved:

* **Non-Blocking Game Loop:** Replaced synchronous input prompts with asynchronous keyboard state tracking (`GetAsyncKeyState`), allowing the environment to update continuously while waiting for player commands.
* **Parallel Array State Management:** Instead of heavy objects or nested loops (which bottlenecked rendering), the game uses parallel arrays to manage the Cartesian coordinates (`x`, `y`), health, and trajectory of multiple bullets and enemies simultaneously in $O(n)$ time.
* **Dynamic Pointer Tracking:** Utilized pointers (`*ptrpx`, `*ptrpy`) for memory-efficient, real-time updates to the player's position.
* **Modular Architecture:** The source code is highly organized into over 30 distinct function prototypes categorized by domain (UI Rendering, Player Mechanics, Enemy AI, Projectile Physics), ensuring clean and maintainable logic.

## ✨ Key Features
* **Tiered Enemy AI:** Three types of enemies (Unarmed, Armed, and Boss) with varying health pools and attack capabilities.
* **Real-Time Collision Detection:** Instantaneous coordinate-matching for bullets, lasers, and entity hitboxes.
* **Procedural Generation:** The extraction spaceship spawns randomly in designated zones to increase replayability.
* **Immersive Console UI:** Includes ASCII graphics, a typewriter-effect introductory storyline, and integrated `windows.h` frequency-based sound effects.

## 💻 Tech Stack
* **Language:** C++ 
* **Core Libraries:** `<iostream>`, `<windows.h>`, `<conio.h>`, `<random>`
* **Environment:** Windows CLI

## 🚀 Installation & Setup

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/yourusername/stellar-survival.git](https://github.com/yourusername/stellar-survival.git)
