#!/bin/bash
. ./variablesetup.sh
export PATH="$DESTINATION/gcc-cross-$GCCVERSION/bin:$DESTINATION/gcc-$GCCVERSION/bin:$PATH"
echo "Path set to:"
echo "$PATH"
