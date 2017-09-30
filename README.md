# shell
Library for Shells;
defines semantics for Shell language primitives:
just add a parser
==========
Back-end/library for command Shells

Defines/implements the semantics for Shell language primitives:

Just add a parser/front-end!

-----
This will provide a starting point for:

- ThrEll (Thread Shell): lighter-weight command shell
  (i.e., runs commands in threads, instead of processes)
- SeaShell: (will use ThrEll)
  - accepts C input
  - compiles a loadable module from that input
  - dynamically loads that module
  - execs a function in that module
- YellShell:
  - Speech-to-text with a custom model file,
    optimized for structured languages and special characters,
    especially C
