#pragma once

#include <QString>
#include <QStringList>
#include <QList>
#include <QHash>

struct SchedInfo {
    QString bare;
    QString display;
    QString category;
    QString desc;
    QStringList modes;
};

inline const QList<SchedInfo> ALL_SCHEDULERS = {
    {"bpfland", "BPFland", "Gaming / Interactive",
     "vruntime-based scheduler that prioritises interactive tasks which block frequently. "
     "Cache-topology aware — keeps tasks near their L2/L3 cache. Good all-round desktop choice.",
     {"auto", "gaming", "lowlatency", "powersave", "server"}},

    {"lavd", "LAVD", "Gaming / Low Latency",
     "Latency-Aware Virtual Deadline scheduler. Assigns deadlines based on latency criticality. "
     "Core Compaction keeps active cores at high frequency. Autopilot switches power profiles automatically.",
     {"auto", "gaming", "lowlatency", "powersave", "server"}},

    {"rusty", "Rusty", "Desktop / Server",
     "Partitions CPUs by last-level cache domain to minimise cross-cache migration. "
     "Scales well on high core-count machines. Hybrid BPF + userspace design.",
     {"auto", "gaming"}},

    {"flash", "Flash", "Desktop / Soft RT",
     "Prioritises fairness and predictability. Suited to batch work, encoding, and audio.",
     {"auto", "gaming", "powersave"}},

    {"cosmos", "Cosmos", "General Purpose",
     "Locality-first scheduler. Uses local DSQs when not saturated, switching to deadline "
     "policy under load. 10µs default time slices; low overhead.",
     {"auto", "gaming", "lowlatency", "powersave", "server"}},

    {"layered", "Layered", "Power Users",
     "Classifies threads into named layers with independent scheduling policies. "
     "Very flexible but needs a JSON config file.",
     {"auto"}},

    {"nest", "Nest", "Lightly Loaded",
     "Places tasks on already-warm, high-frequency cores to keep turbo boost active. "
     "Best when CPU utilisation is low to moderate.",
     {"auto", "powersave"}},

    {"p2dq", "P2DQ", "Mixed Desktop / Server",
     "Pick-2 randomised load balancing keeps queues shallow. Low scheduler overhead. PELT-based load tracking.",
     {"auto", "gaming", "powersave", "server"}},

    {"tickless", "Tickless", "Cloud / HPC",
     "Routes scheduling through a small pool of primary CPUs so others can run tickless. "
     "Reduces OS noise for VMs and HPC workloads.",
     {"auto", "powersave", "server"}},

    {"simple", "Simple", "Reference / Testing",
     "Minimal FIFO/least-runtime policy. No topology awareness. Useful as a benchmark baseline.",
     {"auto"}},

    {"beerland", "Beerland", "Gaming / Desktop",
     "Reduced-overhead variant of bpfland by the same author. Drops expensive per-task tracking "
     "for lower scheduler overhead on busy systems.",
     {"auto", "gaming", "lowlatency", "powersave", "server"}},

    {"rustland", "Rustland", "Userspace / Educational",
     "Predecessor to bpfland with similar logic but running in userspace (Rust). "
     "Higher context-switch overhead; more readable for learning.",
     {"auto"}},
};

inline QString humanizeSched(const QString &bare) {
    static const QHash<QString, QString> overrides = {
        {"bpfland",  "BPFland"},
        {"beerland", "Beerland"},
        {"rustland", "Rustland"},
        {"lavd",     "LAVD"},
        {"p2dq",     "P2DQ"},
    };
    const auto it = overrides.constFind(bare);
    if (it != overrides.cend())
        return it.value();
    if (bare.isEmpty())
        return bare;
    QString s = bare;
    s[0] = s[0].toUpper();
    return s;
}

inline QString humanizeMode(const QString &mode) {
    static const QHash<QString, QString> map = {
        {"auto",       "Auto"},
        {"gaming",     "Gaming"},
        {"lowlatency", "Low Latency"},
        {"powersave",  "Power Save"},
        {"server",     "Server"},
    };
    return map.value(mode.toLower(), mode);
}

inline const char *ERR_NO_POLKIT =
    "pkexec was not found.\n\n"
    "Install it with:\n  sudo apt install polkitd pkexec\n\n"
    "Then log out and back in so a PolKit agent starts.";

inline const char *ERR_SWITCH_FAILED =
    "Switching the scheduler failed.\n\n"
    "Common causes:\n"
    "  - No PolKit authentication agent is running\n"
    "  - scx_loader.service is not active\n\n"
    "Try:  systemctl status scx_loader.service";

inline const char *ERR_STOP_FAILED =
    "Stopping the scheduler failed.\n\n"
    "Try:  pkexec scxctl stop";

inline const char *ERR_PERSIST_ENABLE =
    "Could not enable auto-start.\n\n"
    "Try:  sudo systemctl enable --now scx_loader.service";

inline const char *ERR_PERSIST_DISABLE =
    "Could not disable auto-start.\n\n"
    "Try:  sudo systemctl disable --now scx_loader.service";
