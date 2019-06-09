# MineSweeper
A remake of the classic windows game "Minesweeper". Clear the board of mines by marking each one to ensure that the area is safe.

## Compiling

### Windows
You must install allegro 4 and the allegro loadpng addon:
- [Allegro 4](http://liballeg.org/api.html)


Open code blocks project, select debug as the build target and build


### Linux
```sudo apt-get install liballegro4-dev```

```sudo apt-get install libloadpng4-dev```

Open code blocks project, select debug-linux as the build target and build

## Linking
In case you are not using the code blocks project provided
```
-lloadpng
-lalleg44 or -lalleg
```
