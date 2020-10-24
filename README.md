# Gosh

Simple and easy to use cross-platform window system API.

It aims to be similar to SDL, but more lightweight, and designed around giving you easy access to the window's buffer in software.

## Try the demo

Just run this command in the root of the repository!:

```bash
make debug
```

## Build and install

If you just built the debug version, be sure to clean first:

```bash
make clean
```

(Otherwise you won't get optimizations!)

When you are ready to build and install:

```bash
make install
```

## TODO

### General

_Nothing right now...!_

### X11

- Keysym / text input handling
- Mouse dragging events
- Some kind of X11 vsync mechanism and associated event
- Filter out repeat resize events in event queue (to avoid resize drawing lag)
- Proper generic color handling in X11
- X11 MIT-SHM extension when available

### Backends

- Auto detect backend (with environment variable override)
- Win32 backend
- Wayland backend
- MacOS backend
