# Final Project

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

# Brick Breaker

Author: Connell Hecht

---

## Goal
I will be creating a replica version of brick breaker in C++. Brick breaker is a game where the user controls a moving platform at the bottom of the screen and uses the platform to bounce a ball into bricks that need to be broken. Once all of the bricks are broken, the level is completed. I will hopefully implement power ups and other interesting things like the real game.

## Experience
I have very little background knowledge about this project. I've played brick breaker before but besides that, I have no experience with generating graphics or anything like that. The reason that I want to do this project is I think it will be a cool challenge and it is unlike anything I have ever done before. It seems like C++ is a good language to do this in because video games require fast processing speed.

## Plan
I will use Cinder for the graphics. As far as I can tell, Cinder should be capable of supporting the full graphics implementation, however if it turns out to not be sufficient, I will use LiquidFun (https://github.com/google/liquidfun/tree/master/liquidfun) or Box2D (https://github.com/erincatto/box2d) (LiquidFun is based off of Box2d). For my additional library, I will use OpenAL (https://www.openal.org/) because I think it will provide better audio support than the Cinder audio library.

**End of Week 1**
- Complete basic code structure
- Have basic UI set up (without functionality)
- Select sounds for different actions in game

**End of Week 2**
- Set up physics in game and be able to move platform at bottom of screen
- Have created one simple level to play

**End of Week 3**
- Implement more levels with greater complexity
- Implement power-up features
- Make bricks that are of different types

**This schedule is tentative and will likely change depending on the true difficulty of each task which I have no way of knowing right now**

## Extra features (time permitting)
- Create random level generator to allow for infinitely varied gameplay
- Allow user to specify difficulty
- Allow user to change theme of graphics
- Add support for a gamepad using Cinder Gamepad (https://github.com/halogenica/Cinder-Gamepad)


