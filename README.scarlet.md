# OpenJDK 21 for Scarlet

This branch ports OpenJDK 21.0.13+9 to the Scarlet Native ABI on AArch64.
The upstream base is `ba94eace682733f66e623c089bcafcf4a1b8e39c` (tag
`jdk-21.0.13+9`). Keep upstream updates on `master`; maintain the native port on
`scarlet-21`.

The initial runtime uses HotSpot Zero, Serial GC, a static JNI symbol registry,
and the Scarlet C/C++ runtime. It runs Java bytecode; it does not contain a JIT.
The target is `aarch64-unknown-scarlet`, with `SCARLET` HotSpot OS selection.

## Build and integration

The pinned toolchain, reproducible build driver, static JNI launcher, and guest
validation live in [Scarlet](https://github.com/petitstrawberry/Scarlet), under
`tools/openjdk/`. The Scarlet driver downloads an exact commit of this fork
and verifies its archive SHA-256. This repository is the source of truth for
the OpenJDK platform changes; no extra source overlay should be needed.

The kernel must supply `GetMemoryInfo` (53), `MemoryQuery` (703), and
`MemoryReadWord` (704), and native pthread/futex, TLS, memory protection, and
file operations. `MemoryReadWord` supplies fault-tolerant scalar reads for
HotSpot without POSIX signals.

## Current execution coverage

An AArch64 QEMU guest has executed the real JNI invocation path, `java -version`,
Java Hello, four platform threads with atomics and thread locals, 128 MiB of
transient allocations with Serial GC, and regular-file write/read across the
native 64 KiB I/O boundary. Guest process termination is checked separately
from test output.

This is an initial headless `java.base` port, not a TCK-certified JDK. Other
architectures, JIT, desktop modules, dynamically loaded JNI libraries, native
agents, PerfData, NUMA, large pages, OS thread priorities, POSIX signal handlers,
process creation, and native networking/NIO libraries are outside the validated
runtime. Unsupported port entry points return errors or throw exceptions.
The native C formatter does not yet print floating-point GC timing fields.

The upstream OpenJDK licensing and copyright notices remain in place. See
`LICENSE`, `ADDITIONAL_LICENSE_INFO`, and the per-file headers.
