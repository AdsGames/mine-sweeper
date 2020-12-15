# MineSweeper

A remake of the classic windows game "Minesweeper". Clear the board of mines by marking each one to ensure that the area is safe.

## Getting started

### Windows (MSYS2)

#### Install Libraries

```bash
https://www.allegro.cc/files/?v=4.4
```

#### Build

```bash
cmake -G "MSYS Makefiles" .
```

```bash
make
```

### Mac OS

#### Install Libraries

```bash
https://github.com/msikma/liballeg.4.4.2-osx
```

#### Build

```bash
cmake -G "Unix Makefiles" .
```

```bash
make
```

### Linux

#### Install Libraries

```bash
sudo apt-get install liballegro4-dev libloadpng4-dev liblogg4-dev
```

#### Build

```bash
cmake -G "Unix Makefiles" .
```

```bash
make
```
