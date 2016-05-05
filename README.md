asmblr
==================

Assembly goes in, executables come out. You can't explain that!

asmblr is an assembler for a nonstandard ASM dialect. It outputs ELF binaries, although the header is currently static.

Functionality
------------------

asmblr is capable of parsing through an arbitrary number of statements, with which it generates an AST. This AST is used to emit the corresponding machine code for the instructions, and generates a binary executable with this machine code. By default, the output file is named `asmbld.o`. Every output is automatically prefixed with an ELF header section.

Operands are matched by a predefined number of arguments each mnemonic takes. This means that passing a variable number of operands is not supported, however I'm not aware of any instructions in which a different number of operands can be supplied.

The currently recognized commands are `ret`, `or`, and `mov`. These were chosen for convenience of testing, as each takes a different number of arguments (0, 1, and 2, respectively). As asmblr outputs (mostly) valid executables, the instruction set it supports is currently being expanded.

GPL v3 license.
