#!/bin/sh

[ -z "$1" ] && exit 1
sed -E "s/$(echo "$1" | sed 's/\([][(){}\^.*+?$|]\)/\\\1/gi')/$(echo "$1" | sed -E 's/./*/g')/g"
