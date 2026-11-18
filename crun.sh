#!/usr/bin/env bash

set -u

if [[ $# -ne 1 ]]; then
  printf 'Usage: %s <source.c>\n' "$0" >&2
  exit 2
fi

script_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
source_file=$1

# Resolve a relative source path from the current directory, then from compilerLab.
if [[ ! -f "$source_file" && "$source_file" != /* ]]; then
  source_file="$script_dir/$source_file"
fi

if [[ ! -f "$source_file" ]]; then
  printf 'Error: source file not found: %s\n' "$1" >&2
  exit 2
fi

if [[ "$source_file" != *.c ]]; then
  printf 'Error: expected a C source file ending in .c: %s\n' "$source_file" >&2
  exit 2
fi

source_dir=$(cd -- "$(dirname -- "$source_file")" && pwd)
source_name=$(basename -- "$source_file")
executable="${source_name%.c}"
executable_path="$source_dir/$executable"

printf 'Compiling %s with gcc...\n' "$source_file"
if ! gcc -Wall -Wextra -std=c11 "$source_dir/$source_name" -o "$executable_path"; then
  exit 1
fi

printf 'Running %s...\n' "$executable"
(
  cd -- "$source_dir" || exit 1
  "./$executable"
)
