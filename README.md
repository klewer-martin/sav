# SAV - Sorting Algorithms Visualized

The idea is to develop a visual program that shows how an array is being sorted

Written in C using SDL2 library for graphics

![sav](https://user-images.githubusercontent.com/64109770/182065206-e766b30e-6f7d-4232-b1d2-de840974892d.gif)

## Dependencies
- [SDL2](https://www.libsdl.org/)
- [SDL2-ttf](https://github.com/libsdl-org/SDL_ttf/releases)

## Building and running
```console
$ make -j $(nproc)
$ ./sav
```

## Keybindings

- `space` - start/stop the sorting.
- `tab` - change sorting algorithm.
- `S` - change array shuffle method (random, in order, reversed).
- `R` - restart.

## Font

The font used is [Victor Mono Regular](https://rubjo.github.io/victor-mono/)

## License
[MIT](./LICENSE)
