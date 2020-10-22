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

- Cross platform keycode layer
- Mode option to pass to backend constructor:
  - SYNC (wait for events)
  - ASYNC (poll for events and send idle events when no other events are ready)
  - VSYNC (wait for time to draw and send vsync events)

### X11

- X11 MIT-SHM extension when available
- Some kind of X11 vsync mechanism and associated event
- Proper generic color handling in X11
- Fix issue where it apparently sends a bad message to X when closing the window
- Mouse dragging events
- Mouse button handling
- Keysym handling

### Backends

- Auto detect backend (with environment variable override)
- Win32 backend
- Wayland backend
- MacOS backend
- Linux framebuffer backend
