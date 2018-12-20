#!/bin/sh

pid=$1

input="$(
sudo gdb -n -q -batch \
  -ex "attach $pid" \
  -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
  -ex "call \$dlopen(\"$2\", 1)" \
  -ex "detach" \
  -ex "quit"
)"

last_line="${input##*$'\n'}"

echo "$last_line"
