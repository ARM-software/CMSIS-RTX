#!/usr/bin/env bash

# Script for generating RTX libraries
echo "RTX library generation"

# Usage instructions
usage() {
  echo "Usage: $0 -t TOOLCHAIN"
  echo "Options:"
  echo "  -t    Select the build toolchain [AC6, GCC, CLANG, IAR]"
  exit 1
}

# Build library
build_lib() {
  local lib_dir=""
  local lib_ext=""
  local lib_ctx=""

  # Toolchain selection
  case "$toolchain" in
    "AC6")
      lib_dir="ARM"
      lib_ext="lib"
      lib_ctx=(v6M v7M v8M v7A)
      ;;
    "GCC")
      lib_dir="GCC"
      lib_ext="a"
      lib_ctx=(v6M v7M v8M v7A)
      ;;
    "CLANG")
      lib_dir="CLANG"
      lib_ext="a"
      lib_ctx=(v6M v7M v8M)
      ;;
    "IAR")
      lib_dir="IAR"
      lib_ctx=(v6M v7M v8M v81M v7A)
      lib_ext="a"
      ;;
    *)
      echo "Invalid toolchain: $toolchain"
      usage
      exit 1
      ;;
  esac
  echo "Toolchain: $toolchain"

  echo "Building libraries ..."

  # Check if the library destination directory exists
  if [ -d "$lib_dir" ]; then
    # If it exists, clean it up
    rm -rf "./$lib_dir"/*."$lib_ext"
  else
    # If it doesn't exist, create it
    mkdir -p "$lib_dir"
  fi

  # Library context
  context=()
  for ctx in ${lib_ctx[@]}; do
    context+=$(echo " --context +ARM$ctx"*)
  done

  # Build libraries
  cbuild RTX_Library.csolution.yml --packs --update-rte $context --toolchain $toolchain

  # Copy built libraries
  find out/ -name "*.$lib_ext" -exec cp -r {} "./$lib_dir" \;

  # Clean-up
  rm -rf out/
  rm -rf tmp/
  rm -rf RTE/
  rm RTX_Library*.cbuild*.yml
}

# Check if no input arguments were provided
if [ $# -eq 0 ]; then
  usage
fi

# Parse command-line options
while [[ $# -gt 0 ]]; do
  case "$1" in
    -t)
      shift
      toolchain=$1
      ;;
    *) echo "Invalid option: $1" >&2; usage;;
  esac
  shift
done

# Build library
build_lib
