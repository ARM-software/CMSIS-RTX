#!/usr/bin/env bash

# Script for linting RTX library source code
echo "Lint RTX library source code"

# Usage instructions
usage() {
  echo "Usage: $0 target"
  echo "  target:"
  echo "    ARMv6M"
  echo "    ARMv7M"
  echo "    ARMv7M_FP"
  echo "    ARMv8MBL"
  echo "    ARMv8MML"
  echo "    ARMv8MML_FP"
  echo "    ARMv7A"
  exit 1
}

# Lint RTX
lint_rtx() {
  local target=$1
  local target_opt=""

  # Check target
  case "$target" in
    "ARMv6M")
      target_opt="-march=armv6-m"
      ;;
    "ARMv7M")
      target_opt="-march=armv7-m"
      ;;
    "ARMv7M_FP")
      target_opt="-march=armv7e-m+nodsp"
      ;;
    "ARMv8MBL")
      target_opt="-march=armv8m.base"
      ;;
    "ARMv8MML")
      target_opt="-march=armv8m.main -mfpu=none"
      ;;
    "ARMv8MML_FP")
      target_opt="-march=armv8m.main"
      ;;
    "ARMv7A")
      target_opt="-march=armv7a"
      ;;
    *)
      echo "Invalid target: $target"
      usage
      exit 1
      ;;
  esac

  # Check if PC-lint is available
  lint_path=$(which lint-nt 2>/dev/null)
  if [ -z "$lint_path" ]; then
    echo "Error: PC-lint not found (lint-nt)"
    exit 1
  fi

  # Check if Arm Compiler is available
  armclang_path=$(which armclang 2>/dev/null)
  if [ -z "$armclang_path" ]; then
    echo "Error: Arm Compiler not found (armclang)"
    exit 1
  fi

  # Check if CMSIS-Toolbox is available
  csolution_path=$(which csolution 2>/dev/null)
  if [ -z "$csolution_path" ]; then
    echo "Error: CMSIS-Toolbox not found (csolution)"
    exit 1
  fi

  # Check if Python is available
  python_path=$(which python 2>/dev/null)
  if [ -z "$python_path" ]; then
    echo "Error: Python not found (python)"
    exit 1
  fi

  # Check if Python PyYAML module is intalled
  python_pyyaml=$(pip show PyYAML 2>/dev/null | grep "Name:")
  if [ -z "$python_pyyaml" ]; then
    echo "Error: Python PyYAML module not installed"
    echo "Execute command: pip install pyyaml"
    exit 1
  fi

  # Generate Arm Compiler Preprocessor Symbols
  echo "Generating Arm Compiler Preprocessor Symbols ..."
  touch Dummy.c
  armclang --target=arm-arm-none-eabi $target_opt -E -dM Dummy.c >lnt/armclang_$target.h
  rm -f Dummy.c

  # Generate csolution build and configuration files
  echo "Generating csolution build and configuration files ..."
  csolution convert RTX_Library.csolution.yml -c +$target --toolchain AC6

  # Generate lint option file
  echo "Generating lint option file ..."
  python gen_lnt.py RTX_Library.Library+$target ${armclang_path%"/bin/armclang"}

  # Lint RTX library source code
  echo "Linting RTX library source code ..."
  lint-nt RTX_Library.Library+$target.lnt
}

# Check if target argument was provided
if [ $# -ne 1 ]; then
  usage
fi

# Lint RTX
lint_rtx $1
