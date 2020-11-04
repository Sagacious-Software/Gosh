#!/bin/env bash

# simply run this script to maintain a git mirror of this darcs repository

MIRROR_DIR="mirror"

if [ ! -d $MIRROR_DIR ]; then
  mkdir $MIRROR_DIR
  git init $MIRROR_DIR
  touch $MIRROR_DIR/git.marks
fi

darcs convert export --read-marks darcs.marks --write-marks darcs.marks | (cd $MIRROR_DIR && git fast-import --import-marks=git.marks --export-marks=git.marks)
