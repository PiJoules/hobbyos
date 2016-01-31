# Hobby OS development
Just doing this for fun and learning something new.

Currently, the only supported features are printing and writing to the screen.

This .iso can be saved on and run from a bootable flash drive.


## Dependencies
The number of requirements depends on if you want to build the hosted cross compiler. The hosted cross compiler is not required for building what is in this repo, but when I decide I am at at the point when I am able to port 3rd party software onto this, a hosted cross compiler will be needed to build for the host system.

Any version numbers I also give below were the versions of these programs I used on my computer. I have not tested it with other versions.

### Base Dependencies
- **qemu/qemu-system-i386** for emulating the os, though a .iso can be built and installed on a bootable floppy.
- **make** for bulding everything. I use version 3.81.
- **wget** for downloading gcc, binutils, and any other tools necessary for building this. This is probably already installed.
- **grub-mkrescue** for creating the .iso packed with the grub bootloader.

### Hosted Cross Compiler Dependencies (Optional)
Most of these are just programs used to build `configure` files and `Makefile`s.
- **m4** (1.4.17)
- **autoreconf** (2.64)
- **autoconf** (2.64)
- **automake** (1.11.1)


## Building
If God is willing, this should be all you need to run. Otherwise, I wish you best of luck in fixing it.

### Tools setup (done once)
Before anything can be built, we need the cross compiler to build everything in a different format. For now, the format is i686-elf, but if the hosted cross compiler is used, the format will be something like i686-hobbyos to indicate a new host/target format.

**Unless you plan to change the source code for the tools, you only need to build the tools once.**

1) Inside `variablesetup.sh`, change the value for `WORKINGDIR` to the path of wherever you cloned this repo.

2) Inside `tools.sh`, change the values for `SKIPBINUTILSCROSS`, `SKIPGCCCROSS`, and `SKIPDOWNLOAD` from `1` to `0`.
```sh
export SKIPBINUTILSCROSS=0  # Build the binutils for the cross compiler
export SKIPGCCCROSS=0  # The cross compiler will be gcc
export SKIPDOWNLOAD=0  # Download the binutils and gcc source
```

3) Run `tools.sh` to download the source and build the cross compiler.


### The .iso
If everything was installed correctly, you just need to run `iso.sh` to build the .iso.

To place th .iso onto a bootable floppy, run the following command, replacing `/dev/sdb` with whatever your usb drive is. `/dev/sdb` is the drive on my computer.

```sh
$ sudo dd if=hobbyos.iso of=/dev/sdb && sync
```

At this point, you should be able to boot this feeble os from the usb stick.


## Stuff I learned/hate myself for not knowing already
- Header files are literally just copied and pasted into the .c file wherever #include "header" is placed. Up to this point, the only reason for why I use them is so I can declare functions first, then define them later. This explains why I don't need to include a header file in my list of files to compile when compiling.


## Notes/other stuff
- Inside `condig.sh`, I added `-Werror` as a C flag to treat all warnings as errors. If you are unable to build, and have absolutely no idea what the problem is, remove `-Werror` from the list of C flags.


## TODO
- Continue to fix terminal (scrolling, newlines, ...)
- Add scancode table to print out actual characters.


## History
- 20160131
  - Figured out how to move the cursor.


## References
- [OSDev](http://wiki.osdev.org/Main_Page) for practically almost everything.
