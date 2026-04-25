# Hunter

**Hunter** is a 2D arcade shooting game prototype inspired by the classic **Duck Hunt** style of gameplay.

I created this project as a **practice project at the end of the semester** to improve my Unreal Engine C++ skills by building a simple wave-based shooting game with scoring, spawning logic, win/lose conditions, and mouse-based aiming.

---

## Overview

In **Hunter**, the player controls a gun and shoots birds that appear in waves across the screen.  
The objective is to hit enough birds before the wave ends in order to progress, otherwise the game ends in failure.

The project focuses on arcade gameplay fundamentals such as:

- mouse-controlled aiming
- shooting mechanics
- enemy spawning
- score tracking
- wave progression
- game over / continue logic

---

## Gameplay Features

- **Mouse-based aiming**
  - The gun rotates to follow the cursor
  - The player can aim freely and shoot toward the mouse position

- **Shooting system**
  - Bullet actors are spawned from the gun
  - Bullets travel toward the aimed direction
  - Bullets are destroyed when leaving the gameplay area or hitting a bird

- **Bird enemies**
  - Birds spawn repeatedly in waves
  - Move horizontally across the level
  - Can be destroyed by player bullets
  - Count as escaped if they leave the screen

- **Wave progression**
  - The spawner creates a limited number of birds
  - The player must destroy enough birds to continue
  - If the player fails to meet the requirement, the game ends

- **Score system**
  - Each bird kill adds score
  - Score is managed through the GameMode

- **Start delay**
  - At the beginning of the level, player input and bird spawning are temporarily disabled
  - After the delay, gameplay begins

---

## Game Flow

At the start of the game:

1. Player input is disabled for a few seconds
2. Bird spawning is also disabled
3. After the delay, the player gains control
4. Birds begin spawning in waves
5. The player must shoot enough birds before all birds are spawned and resolved

If enough birds are destroyed, the game loads the **continue level**.  
If not, the game loads the **game over level**.

---

## Technical Focus

This project helped me practice the following Unreal Engine gameplay systems:

- C++ gameplay actor creation
- pawn setup and input binding
- mouse-to-world aiming logic
- projectile spawning and movement
- collision and overlap handling
- timed game start flow
- enemy wave spawning
- score management using GameMode
- win/lose condition handling
- level transition logic

---

## Tech Stack

- **Engine:** Unreal Engine
- **Language:** C++
- **Framework/Modules:** Unreal Engine Gameplay Framework, Paper2D
- **Project Type:** Semester practice project

---

## Main Classes

### `APlayerGun`
Handles:
- player pawn setup
- mouse-based gun rotation
- shooting input
- bullet spawning

### `ABullet`
Handles:
- projectile movement
- collision with birds
- bullet destruction when leaving bounds or on hit

### `ABird`
Handles:
- bird movement
- collision with bullets
- notifying the GameMode when destroyed or escaped

### `ABirdSpawner`
Handles:
- timed bird spawning
- wave setup
- limiting total bird count

### `AHunterGameModeBase`
Handles:
- score tracking
- counting killed birds
- counting escaped birds
- enabling gameplay after the start delay
- deciding whether the player wins or loses the wave

---

## What I Learned

This project helped me become more comfortable with building a complete gameplay loop in Unreal Engine using C++.

Through this prototype, I practiced:

- implementing a player-controlled shooter system
- creating wave-based enemy spawning
- handling simple arcade progression
- connecting gameplay events to score and level flow
- using timers and GameMode logic to control game state

It was an important practice project for improving my understanding of gameplay programming and arcade game structure.

---

## Project Purpose

This project was created as **practice at the end of the semester**.

Its purpose was to help me apply the programming concepts I had learned and turn them into a complete small game prototype inspired by a classic arcade formula.

---

## Future Improvements

Possible future improvements for this project include:

- multiple bird types with different speeds
- more advanced wave progression
- ammo system / reload mechanic
- UI for score, wave status, and remaining birds
- sound and visual feedback polish
- difficulty scaling between waves
- more polished menu and transition screens

---

## Status

**Completed as a semester practice project**

---

## Author

**George Bolias**  
Game Programmer / Unreal Engine Developer

- Portfolio: [https://www.georgebolias.com/](https://www.georgebolias.com/)
- LinkedIn: [https://www.linkedin.com/in/georgebolias/](https://www.linkedin.com/in/georgebolias/)
- GitHub: [https://github.com/GamingMystae](https://github.com/GamingMystae)
