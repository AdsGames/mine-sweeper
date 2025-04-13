# MineSweeper

[![Reliability Rating](https://sonarcloud.io/api/project_badges/measure?project=AdsGames_mine-sweeper&metric=reliability_rating)](https://sonarcloud.io/summary/new_code?id=AdsGames_mine-sweeper)
[![Security Rating](https://sonarcloud.io/api/project_badges/measure?project=AdsGames_mine-sweeper&metric=security_rating)](https://sonarcloud.io/summary/new_code?id=AdsGames_mine-sweeper)
[![Maintainability Rating](https://sonarcloud.io/api/project_badges/measure?project=AdsGames_mine-sweeper&metric=sqale_rating)](https://sonarcloud.io/summary/new_code?id=AdsGames_mine-sweeper)

A remake of the classic windows game "Minesweeper". Clear the board of mines by marking each one to ensure that the area is safe.

## Demo

[Web Demo](https://adsgames.github.io/mine-sweeper/)

## Setup

### CMake

```bash
cmake --preset debug
cmake --build --preset debug
```

### Build Emscripten

```bash
emcmake cmake --preset debug
cmake --build --preset debug
```
