#pragma once

#include <QString>
#include <QStringList>
#include <QPair>

struct SchedulerInfo {
    QString bare;
    QString display;
    QString category;
    QString desc;
    QStringList modes;
};

static const QList<SchedulerInfo> ALL_SCHEDULERS = {
    {"bpfland", "BPFland", "Gaming / Interactive",
     "A vruntime-based scheduler prioritising interactive tasks that block frequently. "
     "Cache-topology aware — keeps tasks near their L2/L3 cache. Recommended default for "
     "desktop and gaming.",
     {"auto", "gaming", "lowlatency", "powersave", "server"}},
    {"lavd", "LAVD", "Gaming / Low Latency",
     "Latency-Aware Virtual Deadline scheduler. Computes a latency-criticality score per "
     "task and assigns virtual deadlines. Core Compaction keeps active cores at high "
     "frequency. Autopilot mode auto-switches between performance/balanced/powersave.",
     {"auto", "gaming", "lowlatency", "powersave", "server"}},
    {"rusty", "Rusty", "Desktop / Server",
     "Partitions CPUs by last-level cache domain to minimise cross-cache migration. "
     "Good scalability on high core-count systems. Hybrid BPF + userspace design.",
     {"auto", "gaming"}},
    {"flash", "Flash", "Desktop / Soft RT",
     "Emphasises fairness and predictability over prioritising interactive tasks. "
     "Good for batch, encoding, and audio workloads.",
     {"auto", "gaming", "powersave"}},
    {"cosmos", "Cosmos", "General Purpose",
     "Lightweight locality-first scheduler. Keeps tasks on the same CPU using local "
     "DSQs when not saturated. Under load switches to deadline-based policy. "
     "10µs default time slices. Low overhead general-purpose choice.",
     {"auto", "gaming", "lowlatency", "powersave", "server"}},
    {"layered", "Layered", "Power Users",
     "Classifies threads into named layers (like cgroups) with independent scheduling "
     "policies per layer. Highly flexible but requires manual JSON config.",
     {"auto"}},
    {"nest", "Nest", "Lightly-Loaded",
     "Places tasks on already-warm, high-frequency cores to keep turbo boost active. "
     "Effective when CPU utilisation is low to moderate.",
     {"auto", "powersave"}},
    {"p2dq", "P2DQ", "Mixed Desktop/Server",
     "Pick-2 randomised load balancing keeps queues shallow. Simple design means low "
     "scheduler overhead. PELT-based load tracking.",
     {"auto", "gaming", "powersave", "server"}},
    {"tickless", "Tickless", "Cloud / HPC",
     "Routes scheduling through a small pool of primary CPUs, allowing others to run "
     "tickless (no scheduler interrupts). Reduces OS noise for VMs and HPC.",
     {"auto", "powersave", "server"}},
    {"simple", "Simple", "Reference / Testing",
     "Minimal FIFO/least-runtime policy. No topology awareness. Useful as a baseline "
     "for benchmarking and understanding sched_ext.",
     {"auto"}},
    {"beerland", "Beerland", "Gaming / Desktop",
     "A reduced-overhead variant of scx_bpfland by the same author. Strips back "
     "expensive per-task tracking for lower scheduler overhead on busy systems.",
     {"auto", "gaming", "lowlatency", "powersave", "server"}},
    {"rustland", "Rustland", "Userspace / Educational",
     "Predecessor to bpfland with similar logic but running in userspace (Rust). "
     "More readable for learning but adds context-switch overhead.",
     {"auto"}},
};

static const QString ERROR_NO_POLKIT = R"(
No PolKit authentication agent is running.

Please ensure pkexec is installed and available:
  sudo apt install polkitd

Then restart your session or reboot.
)";

static const QString ERROR_SCHED_NOT_INSTALLED = R"(
The selected scheduler is not installed on this system.

Run ./install.sh to install schedulers, or check scxctl list for available options.
)";

static const QString ERROR_MODE_NOT_SUPPORTED = R"(
The selected mode is not supported by this scheduler.

Supported modes: %1
)";

static const QString ERROR_SWITCH_FAILED = R"(
Failed to switch scheduler.

This usually means:
• You're not in a PolKit authentication session
• The scx_loader service is not running
• Another scheduler is already active

Try running: pkexec scxctl status
)";

static const QString ERROR_START_FAILED = R"(
Failed to start scheduler.

Make sure scx_loader.service is active:
  sudo systemctl status scx_loader.service

Then try again.
)";

static const QString ERROR_STOP_FAILED = R"(
Failed to stop scheduler.

This usually means:
• You're not in a PolKit authentication session
• The current scheduler doesn't respond to stop commands

Try running: pkexec scxctl status
)";

static const QString ERROR_PERSIST_FAILED_ENABLE = R"(
Failed to enable auto-start on boot.

Try running manually:
  sudo systemctl enable --now scx_loader.service
)";

static const QString ERROR_PERSIST_FAILED_DISABLE = R"(
Failed to disable auto-start on boot.

Try running manually:
  sudo systemctl disable --now scx_loader.service
)";

static const QString ERROR_SERVICE_NOT_RUNNING = R"(
The scx_loader service is not running.

Start it with: sudo systemctl start scx_loader.service
)";

static const QString KERNEL_UNSUPPORTED_MSG = "Kernel does not support sched_ext (need Linux 6.12+ with CONFIG_SCHED_CLASS_EXT=y). Install a backports kernel and reboot.";
static const QString KERNEL_VERSION_OK_MSG = "Supported — Linux %1";
static const QString KERNEL_MISSING_SYSFS_MSG = "Kernel %1 meets 6.12+ but /sys/kernel/sched_ext not found";
