asmblr
==================

Assembly goes in, executables come out. You can't explain that!

asmblr is a simple assembler for a nonstandard ASM dialect.

Functionality
------------------

Currently, asmblr can parse through an arbitrary number of statements and generate a basic AST for them.

Operands are matched by a predefined number of arguments each mnemonic takes. 

The currently recognized commands are `ret`, `or`, and `mov`. These were chosen for convenience of testing, as each takes a different number of arguments (0, 1, and 2, respectively).

GPL v3 license.
