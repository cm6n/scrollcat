# Scrollcat

## About

A 2D platform game about a cat, built for just for fun. Built in a day (mostly).

## Game play

![Scrollcat](/assets/scrollcat.png)

## How does it work?

Scrollcat is written in C++ and uses SDL2 for the 2D graphics and keyboard management. Today it
builds on Linux, but is theoretically can be cross-platform thanks to the only dependency being
SDL2 and the standard library. Graphics were done in Paint for a retro-blocky vibe. Levels
are read in from text files at run time and can be edited quickly to add new levels or adjust
the difficulty.