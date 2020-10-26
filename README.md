# Gosh

Simple and easy to use cross-platform window system API.

It aims to be similar to SDL, but more lightweight, and designed around giving you easy access to the window's buffer in software.

## Try the demo

Just run this command in the root of the repository!:

```bash
make debug
```

Or if you want to debug the Wine build:

```bash
make winedebug
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

### Windows build from Unix

To build a Windows executable using `winegcc`, be sure to clean first:

```bash
make clean
```

And then run this:

```bash
make winerelease
```

Which will produce a Windows binary!

## TODO

### General

- Setup for multiple demos showcasing different features
- Keeping proper track of closed windows
- Mechanism for detecting when last window is closed
- Consider making backend chosen completely at compile time

### X11

- Complete the keycode mappings
- Proper generic color handling in X11
- Proper vsync!
- Filter out repeat resize events in event queue (to avoid resize drawing lag)
- X11 MIT-SHM extension when available
- Fix "BadDrawable" on attempt to draw while window is closing

### Backends

- Auto detect backend (with environment variable override)
- Windows backend
- Wayland backend
- MacOS backend
