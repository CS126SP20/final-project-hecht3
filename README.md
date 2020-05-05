# Final Project

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

# Brick Breaker

Author: Connell Hecht

---

# Background

This project was created as my final project for CS 126: Software Design Studio at University of Illinois Urbana Champaign.
The code was written with extensibility in mind - I've done my best to make it easy to change the difficulty and complexity of the game through various means (powerups, ball speed, platform size, number of platforms, number of balls, brick location and health, and much more). I made the particle controller/physics myself (most of this functionality is in the my_app.cpp source code). This should hopefully make the game easier to set up because there is no installation of an external physics engine involved. I wanted to make an accurate replica of this game using C++ and I think I've come pretty close in terms of functionality, but the graphics are obviously not the same. The game currently has the first 10 levels coded, however it would be very easy to modify it to include more levels.

# Controls and gameplay

The platform follows the mouse along the bottom of the screen. To move the platform, simply move the mouse. To launch the ball, click the mouse. I have programmed the game so that the ball is affected by the platform's velocity to simulate friction and allow the user to aim the ball as it hits the platform. The game automatically moves on to the next level when you complete the level you are on.

# Dependencies

- Cmake is required to set up this project

**Cinder**

- [Ubuntu](https://www.libcinder.org/docs/guides/linux-notes/ubuntu.html)

- [Windows](https://libcinder.org/docs/guides/windows-setup/index.html)

- [OS X](https://libcinder.org/docs/guides/mac-setup/index.html)

**Cinder Block: poSoundManager**

Clone the following repo and put it into your Cinder/blocks directory:
https://github.com/Potion/Cinder-poSoundManager

Cinder should handle the entire set up once you follow the directions for your respective OS. The cmake list file is already set up to use poSoundManager as a dependency.

