# Hawk Puzzle Solver

Small C program that solves a letter grid puzzle by rotating the leading “hawk” letter through each column until all columns match. The solver reads puzzle strings or files, runs breadth‑first search, and reports the minimum moves to complete the board.

## Layout
- `driver.c` — Entry point with built-in assertions that exercise solver routines and sample board files.
- `md.c` / `md.h` — Core puzzle logic: board parsing/validation, move generation (`hawkpush`), solution search (`solve`), and helper utilities.
- `mydefs.h` — Shared types and constants (`BRDSZ`, `MAXBRDS`, `state`, `board`) plus standard includes.
- `tests/` — Sample boards in text form (`*.brd`, `*.txt`) used by the driver tests; paths are referenced directly from `driver.c`.
- `Makefile` — Targets to build optimized (`md`) or sanitized (`md_d`) binaries, plus `run`, `clean`, and `zip`.

## Usage
```sh
# Build optimized and sanitized binaries
make          # builds md and md_d

# Run the main test harness
make run      # executes ./md
```

Board files use dashed rows like `A-ABC-ABC-ABC-CBA`; the first letter is the hawk, rows are separated by `-`, and uppercase letters fill the grid.
