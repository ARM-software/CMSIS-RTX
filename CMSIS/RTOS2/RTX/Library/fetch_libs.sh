#!/usr/bin/env bash

DIRNAME=$(realpath "$(dirname "$0")")

function fail_and_bail() {
    echo "$1" >&2
    exit 1
}

pushd "${DIRNAME}" >/dev/null || fail_and_bail "Failed to change dir to ${DIRNAME}"

TAG=$(git describe --tags --abbrev=0 --match="v*")

echo "Fetching pre-built libraries from '${TAG}' ..."
gh release download "${TAG}" -p RTX_Lib.tar.bz2 || fail_and_bail "No release with lib archive for latest tag ${TAG}!"

tar -xf RTX_Lib.tar.bz2 || fail_and_bail "Failed to untar lib archive!"

rm RTX_Lib.tar.bz2

exit 0
