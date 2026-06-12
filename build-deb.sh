#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"

dpkg-buildpackage -us -uc

mkdir -p build
mv ../scx-switcher_*.deb build/ 2>/dev/null || true
mv ../scx-switcher-dbgsym_*.deb build/ 2>/dev/null || true

rm -f ../scx-switcher_*.buildinfo ../scx-switcher_*.changes \
      ../scx-switcher_*.dsc ../scx-switcher_*.tar.xz ../scx-switcher_*.tar.gz 2>/dev/null || true

echo "==> Done. .deb in build/"
ls -lh build/scx-switcher_*.deb
