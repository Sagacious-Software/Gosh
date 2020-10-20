# Gosh

Simple and easy to use cross-platform windowing API

It aims to be similar to SDL, but more lightweight, and designed around giving you easy access to the window's buffer

## questions for myself and todo

how to deal with backends?
- include them all?
- compile time switches for which to include??
- require user to specify which it wants???
- implicitely choose depending on which is detected?????
- use env var for this tho

- eventually do win32 and macos
- get a good system for handling COLOR !!!!! 
- figure out the VSYNC
- fix the thing where X complains when u close the window bc it was already closed or something
