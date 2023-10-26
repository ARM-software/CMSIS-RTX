#!/usr/bin/env bash

DIRNAME=$(realpath "$(dirname "$0")")
LATEST=0

# Write error message and exit
function fail_and_bail() {
  echo "$1" >&2
  exit 1
}

# Usage instructions
usage() {
  echo "Usage: $0 [-h|--help] [-l|--latest]"
  echo "Options:"
  echo "  -h    Show usage help"
  echo "  -l    Fetches the libs from latest workflow build instead of release"
  exit 1
}

# Parse command-line options
while [[ $# -gt 0 ]]; do
  case "$1" in
    -l|--latest)
      LATEST=1
      shift
      ;;
    -h|--help)
      usage
      ;;
    *) echo "Invalid option: $1" >&2; usage;;
  esac
  shift
done

pushd "${DIRNAME}" >/dev/null || fail_and_bail "Failed to change dir to ${DIRNAME}"

if [[ $LATEST == 1 ]]; then
  echo "Fetching pre-built libraries from latest workflow run ..."
  gh run download -p RTX_Lib || fail_and_bail "Failed to find workflow run with pre-built library artifact!"
  mv -f RTX_Lib/RTX_Lib.tar.bz2 . || fail_and_bail "Artifact does not contain library tarball!"
  rm -rf RTX_Lib
else 
  TAG=$(git describe --tags --abbrev=0 --match="v*")
  echo "Fetching pre-built libraries from '${TAG}' ..."
  gh release download "${TAG}" -p RTX_Lib.tar.bz2 || fail_and_bail "No release with lib archive for latest tag ${TAG}!"
fi 

tar -xf RTX_Lib.tar.bz2 || fail_and_bail "Failed to untar lib archive!"

rm RTX_Lib.tar.bz2

exit 0
