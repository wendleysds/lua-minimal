# Lua Minimal (Freestanding / Kernel-Oriented Fork)

This repository is a minimal, freestanding-oriented fork of Lua 5.4.8, adapted to run without a hosted C standard library and designed for integration into custom operating systems and kernel-level environments.

It preserves the original Lua source code and copyright notices from PUC-Rio.
Modifications are focused exclusively on portability to freestanding environments and syscall integration.

---

minimal freestanding-oriented fork of Lua adapted to run without a hosted C standard library and designed for integration into custom operating systems and kernel-level environments

## Project Goals

This fork aims to:

* Remove dependency on hosted libc environments
* Support `-ffreestanding` builds
* Replace standard C runtime dependencies with a minimal internal libc
* Allow direct syscall injection from C into Lua
* Enable Lua execution inside custom kernels or minimal userlands

This is not a language modification.
The Lua VM and semantics remain unchanged.

---

## Build Philosophy

This version is designed for:

* `-ffreestanding`
* `-fno-builtin`
* `-nostdlib`
* Static linking
* Custom memory allocators
* Custom `setjmp/longjmp`
* Kernel-provided `time`, `locale`, and math implementations

The build system adds a dedicated target:

```
make lua-minimal
```

Which applies freestanding flags and links against the internal minimal libc.

---

## Replaced / Reimplemented libc Components

To support freestanding execution, the following libc symbols are expected to be provided by the hosting environment:

### Memory and String

* memcpy
* memmove
* memcmp
* memset
* strlen
* strcmp
* strchr
* strspn
* strpbrk

### Control Flow

* _setjmp
* longjmp
* abort

### Math

* fmod
* frexp
* pow
* strtod

### Locale

* localeconv
* strcoll

### Time

* time

### Formatting

* snprintf

These may be implemented by:

* A custom kernel libc
* A minimal embedded libc
* A selectively imported implementation (for example, from musl)

---

Lua sources remain mostly unchanged.
Freestanding adaptations are isolated.

---

## License and Copyright

Lua is free software, distributed under the Lua license.

This fork retains:

* All original copyright notices
* The original Lua license text
* Attribution to PUC-Rio

This project does not alter the Lua license terms.

The original Lua license can be found in:

```
lua/LICENSE
```

For more information about Lua, visit:

[https://www.lua.org](https://www.lua.org)

---

## Intended Audience

This fork is intended for:

* Operating system developers
* Kernel developers
* Embedded systems engineers
* Bare-metal runtime designers

It is not intended as a general-purpose Lua replacement.

---

## Stability Notice

This fork prioritizes:

* Minimalism
* Deterministic behavior
* Kernel compatibility

It may:

* Omit features depending on full libc
* Remove host-dependent behaviors
* Restrict floating point behavior depending on platform

---

## Upstream Compatibility

Core Lua VM behavior remains intact.
Upstream patches can be merged with minimal conflict if freestanding adaptations remain modular.

---

## Acknowledgments

Lua was created and is maintained by the Lua team at PUC-Rio.

This fork exists purely to adapt Lua for freestanding and kernel-level environments, without modifying the language itself.
