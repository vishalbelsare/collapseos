# emul

This is an emulator for a virtual machine that is suitable for running Collapse
OS. The goal of this machine is not to emulate real hardware, but rather to
serve as a development platform. What we do here is we emulate the z80 part,
the 64K memory space and then hook some fake I/Os to stdin, stdout and a small
storage device that is suitable for Collapse OS's filesystem to run on.

Through that, it becomes easier to develop userspace applications for Collapse
OS.

We don't try to emulate real hardware to ease the development of device drivers
because so far, I don't see the advantage of emulation versus running code on
the real thing.

## Usage

First, make sure that the `libz80` git submodule is checked out. If not, run
`git submodule init && git submodule update`.

The Makefile in this folder has multiple targets that all use libz80 as its
core. For example, `make shell` will build `./shell`, a vanilla Collapse OS
shell. `make zasm` will build a `./zasm` executable, and so on.

See documentation is corresponding source files for usage documentation of
each target.