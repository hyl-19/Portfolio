# OurC Interpreter

This repository contains a C++ code, an implementation of the **OurC** interpreter, which supports parsing, checking, and executing a C-like language defined by the *OurC Grammar*.

---

## Overview

The **OurC** interpreter reads commands and programs in a simplified C-like language. It implements:

* A *recursive descent* parser based on the OurC grammar.
* Interactive command interpretation and program execution.
* Support for variables, expressions, control flow (`if`, `while`, `do-while`), functions, and arrays.
* Four phases of coursework projects:

  1. Simple expressions and statements interpreter.
  2. Syntax checker and pretty printer with built-in functions.
  3. Full execution engine for control structures and arrays.
  4. Function call support, extended type handling, and errors.

---

## Grammar

The syntax of OurC is defined in **Our-C-Grammar-2016-07-15.pdf**. Key points:

* **Expressions**: Comma-separated `basic_expression`
* **Unary operators**: `+`, `-`, `!`, `++`, `--`
* **Binary operators**: arithmetic, relational, logical, bitwise, assignment, and the conditional operator `?:`
* **Statements**: null (`;`), expression, compound (`{}`), `if`, `while`, `do-while`, `return`.
* **Function definitions**: support for parameters, local scope, and returns of various types.

Refer to the full grammar specification for details.

---

## Features

* **Interactive REPL** with prompt (`>`) handling single-line and multi-line input.
* **Variable types**: `int`, `float`, `char`, `bool`, `string`, and arrays of fixed size.
* **Operators**: full set including `+=`, `-=`, `*=`, `/=`, `%=` and bit shifts.
* **Control Flow**: `if-else`, `while`, `do-while` with nested blocks.
* **Functions**: global and local scopes, parameter passing (value and array by reference), return values.
* **Built-in I/O**: `cin` and `cout` for input/output operations.
* **Error Detection**:

  * **Lexical**: unrecognized token
  * **Syntax**: unexpected token
  * **Semantic**: undefined identifier
* **Floating-point tolerance**: comparisons within `0.0001` threshold.

---

## Examples

```plaintext
> 2 + 3;
5
> int x;
> x := 10;
10
> x * 2;
20
> if (x > 5) x := x + 1;
> x;
11
> quit
```

For full examples, see the project specification PDFs.

---

## Error Handling

Errors are reported with line numbers and messages:

* **Lexical error**: `unrecognized token with first char : '$'`
* **Syntax error**: `unexpected token : '*'`
* **Semantic error**: `undefined identifier : 'bcd'`

Execution resumes at the next line after an error, according to the project requirements.

