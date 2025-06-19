# Computer Organization

## 🧠 Project Overview

This final project implements a pipelined CPU datapath with five major stages. We designed the architecture using Verilog and verified it with ModelSim simulations.

---

## 📌 Datapath Diagram

Below is our final pipelined CPU datapath, covering instruction fetch, decode, execute, memory, and write-back stages:

![Datapath Diagram](./Computer%20Organization/Single-Cycle_Pipeline_CPU/datapath.png)

---

## 🔧 Architecture Breakdown

### 1. Instruction Fetch (IF)
- Components: PC, ADD, Instruction Memory, PC MUX, Jump MUX, Branch AND gate, IF/ID register.
- Logic:
  - PC MUX decides between PC+4 and branch target.
  - Jump MUX handles jump operations.
  - AND gate checks whether a branch should be taken.

### 2. Instruction Decode (ID)
- Components: Register File, Branch Comparator, Sign Extend, Control Unit (pipelined), ID/EX register.
- Logic:
  - Branch comparator checks if RD1 == RD2.
  - Control unit decodes instruction and signals execution behavior.

### 3. Execute (EX)
- Components: ALU, Multiplier, HiLo register, ALU Control, EX/MEM register, 2-to-1 MUXs.
- Logic:
  - Chooses between register data and extended immediate via ALUSrc MUX.
  - Selects destination register via RegDst MUX.
  - Handles MULTU, MADDU with HiLo logic.

### 4. Memory (MEM)
- Components: Data Memory, MEM/WB register.
- Logic:
  - Reads or writes to memory based on control signals.

### 5. Write Back (WB)
- Components: 2-to-1 MUX, Register File.
- Logic:
  - Determines whether to write ALU or Memory output back to register.

### Multiplier
- Stores `dataA` as the multiplicand and `dataB` as the multiplier.
- In each cycle, checks whether the least significant bit is 1, performs accumulation and shifting.
- Executes this for 32 iterations and outputs the final product.

### Shifter
- Implements a 5-stage Barrel Shifter.
- Each stage uses 2x1 MUXes based on the shift amount.
- A total of 160 MUXes are used.

### HiLo Register
- Receives the 64-bit result from the multiplier.
- Outputs the upper 32 bits to `HiOut`, and the lower 32 bits to `LoOut`.

### MUX
- Implemented using a ternary operator.
- Selects the output based on the control signal.

### ALU Control
- Selects the appropriate operation module (e.g., ALU, Multiplier, Shifter) based on the instruction.
- Generates corresponding control signals.

### TestBench
- Reads test data from a file to verify the module’s correctness.
- Works with ModelSim to generate waveform outputs.

---

## ✅ Instruction Verification Examples

| Instruction         | Operation Check                                     |
|---------------------|-----------------------------------------------------|
| `add $s1, $s2, $s1` | 2 + 3 = 5 → `$s1 = 5`                               |
| `sub $s2, $s0, $s2` | 3 - 1 = 2 → `$s2 = 2`                               |
| `and $s1, $s0, $s2` | 5 & 1 = 1 → `$s2 = 1`                               |
| `or $s2, $s0, $s2`  | 2 \| 1 = 3 → `$s2 = 3`                              |
| `srl $s1, $s2, 1`   | 5 >> 1 = 2 → `$s2 = 2`                              |
| `slt $s1, $s2, $s3` | 5 < 3 = 0 → `$s3 = 0`                               |
| `addiu $s1, $s0, 1` | 5 + 1 = 6 → `$s0 = 6`                               |
| `lw $s1, 0($t7)`    | Load memory → `$s1 = mem[t7 + 0]`                   |
| `sw $zero, 24($s2)` | Store 0 → `mem[s2 + 24] = 0`                        |
| `multu $s3, $s2`    | 0 * 2 = 0 → `HiLo = 0`                              |
| `maddu $s2, $s3`    | 2 * 1 + HiLo = 2 → `HiLo = 2`                       |
| `mfhi $s1`          | `$s1 = Hi`                                          |
| `mflo $s2`          | `$s2 = Lo`                                          |
| `j 7`               | Jump to PC = 28                                     |
| `beq $s1, $s2, 3`   | If $s1 == $s2 → branch taken                        |

---

## 🔍 Simulation Results

- All instruction behaviors verified in ModelSim.
- Waveform results matched expected register/memory updates.
- Pipeline registers confirmed correct data propagation.

