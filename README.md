# Gosh

Simple and easy to use cross-platform window system API.

It aims to be similar to SDL, but more lightweight, and designed around giving you easy access to the window's buffer in software.

## Build

First edit `meson_options.txt` and choose which backends you would like to compile support for.
Set the ones you would like to enable to `enabled` and the rest of them to `disabled`.
Note that if you are on Unix and would like to use the Windows backend you have to have Wine installed (see below).

Then build the library and the demos by running this in the root of the repository:

```bash
meson builddir --buildtype release
cd builddir
meson compile
```

(Optionally do `--buildtype debug` instead if you would like to keep debugging information and turn optimizations off, e.g., if you want to do development.)

### Wine build

If you are on Unix and have Wine installed you can enable the Windows backend option in `meson_options.txt`.

Then do this back in the root of the repository if you would like to do a Wine build:

```bash
CC=winegcc meson buildwine --buildtype release
cd buildwine
meson compile
```

Again, you can change `release` to `debug` if you like!

## Try the demos

Try the demos by running this in the build directory:

```bash
meson test
```

## Install

And when you are ready to install do this in the build directory:

```bash
meson install
```

## TODO

### General

- Setup for multiple demos showcasing different features
- Screenshot/gif
- Proper error handling
- Optimisations optimisations optimisanions !!!!!

### X11

- Complete the keycode mappings
- Proper generic color handling in X11
- Proper vsync!
- Filter out repeat resize events in event queue (to avoid resize drawing lag)
- X11 MIT-SHM extension when available
- Fix "BadDrawable" on attempt to draw while window is closing
- Mechanism for detecting when last window is closed
- Keeping proper track of closed windows

### Backends

- Auto detect backend (with environment variable override)
- Wayland backend
- MacOS backend
