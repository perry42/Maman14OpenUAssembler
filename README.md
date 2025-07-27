
````markdown
# Maman14OpenUAssembler

A C99 assembler project developed as part of the **"Maman 14"** assignment in the Systems Programming course at the Open University of Israel.

## 📘 Project Overview

This assembler translates a simplified custom assembly language into machine code, targeting a **fictional 12-bit architecture** (rather than the standard 8-bit). The assignment replicates constraints found in early computing systems or embedded platforms, making this an excellent deep-dive into low-level systems and memory management.

---

## 🛠 Key Features

- **Two-pass assembler**: Symbol resolution and encoding are separated into clear processing phases.
- **Custom instruction set and memory model**:
  - Memory words are 12 bits wide.
  - Supports labels and directives like `.data`, `.string`, `.entry`, `.extern`
- **Linked data structures**:
  - Linear symbol table
  - Circular external label list
- **Strict syntax validation** with detailed error reporting
- **Modular C99 codebase** with header and source file separation

---

## 🧩 Core Components

### `second_pass.c`
Handles the second phase of compilation:
- Resolves labels and entry references
- Encodes instructions and operands
- Writes `.ob`, `.ent`, and `.ext` output files

### `lables.c`
Implements a symbol table:
- Adds, updates, and removes labels
- Validates `.entry` constraints
- Resolves label addresses and flags

### `externs.c`
Manages external symbol usage:
- Circular list for `.extern` references
- Tracks usage locations for machine code output

---

## 📄 Assignment Context

This project was developed in response to the **Maman 14** assignment.  
You can find the full specification in the [`maman14.pdf`](./maman14.pdf) file included in this repository.

---

## 🚀 Build Instructions

Ensure you are using GCC with the C99 standard:

```bash
gcc -std=c99 -Wall -Wextra -o assembler *.c
````

To run the assembler:

```bash
make
./assembler example.as
```

It will generate:

* `example.ob` — object code
* `example.ent` — entry label references
* `example.ext` — external label references

---

## 📁 Project Structure

```
Maman14OpenUAssembler/
├── assembler.c
├── first_pass.c
├── second_pass.c
├── lables.c
├── externs.c
├── utils.c
├── tools.c
├── MAMAN14.pdf // חוברת הקורס
├── README.md
└── .gitignore
```

> Headers and source files are cleanly organized to reflect modular and maintainable C design.

---

## 🧠 Learning Outcomes

* Implementing a full two-pass assembler from scratch
* Working with pointer-based linked lists
* Handling custom memory models and instruction formats
* Designing modular systems using header files and abstractions
* Parsing and validating custom syntax in C99

---

## 📜 License

This repository is intended for educational purposes and public reference. You are welcome to use and adapt it with proper attribution.

---

## 🙋‍♂️ Author

**Elizur Leiman**
Computer Science student and software engineer
Passionate about systems programming, algorithm design and elegant low-level code
