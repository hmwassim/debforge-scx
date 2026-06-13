# Changelog

All notable changes to SCX Switcher will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Fixed
- Added missing PolKit policy file (`data/com.scx-switcher.policy`)
- Fixed race condition in `PrivOps::writeConfig()` where duplicate callbacks could fire
- Removed duplicate mode map in `privops.cpp`, now uses shared `humanizeMode()` from config.h
- Improved timeout handling to prevent callback duplication
- Made state file writes atomic using temp file + rename pattern
- Enhanced error messages in PrivOps callbacks with descriptive context
- Fixed `build.sh` to use Release build type by default
- Added `--dry-run` option to install.sh for testing without making changes
- Improved installer kernel compatibility check to handle backports/testing kernels

### Added
- PolKit authentication dialog for privileged operations
- Dry-run mode for installation script (`install.sh --dry-run`)
- Better error messages indicating which operation timed out or failed
- Atomic state file writes to prevent corruption on crashes

## [1.1.0] - 2026-06-13

### Fixed
- Removed unnecessary Qt6::Network dependency (only QLocalServer needed)
- Fixed marquee scrolling speed in MainWindow

### Changed
- Updated cmake configuration to use Release build type by default

## [1.0.0] - Initial Release

- First public release of SCX Switcher GUI for managing sched-ext CPU schedulers
