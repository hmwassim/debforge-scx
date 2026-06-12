#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"

mkdir -p build
dpkg-buildpackage -us -uc --output-dir=build

echo "==> Done. .deb in build/"
ls -lh build/scx-switcher_*.deb 2>/dev/null
