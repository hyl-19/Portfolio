# Computer Organization – Final Project

## 🧠 Project Overview

This final project implements a pipelined CPU datapath with five major stages. We designed the architecture using Verilog and verified it with ModelSim simulations.

---

## 📌 Datapath Diagram

Below is our final pipelined CPU datapath, covering instruction fetch, decode, execute, memory, and write-back stages:

![Datapath Diagram](./datapath.png)

> 📝 _Please ensure the file `datapath.png` is uploaded to the GitHub repo for the image to render properly._

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

### ALU
- **1-bit ALU**：支援 AND、OR、ADD、SUB 等基本運算。
- **Full Adder**：由 XOR、AND、OR gate 實現。
- **32-bit ALU**：以 32 個 1-bit ALU 組成，透過 `invert` 控制運算為加法或減法。

### Multiplier
- 將 dataA 儲存為 multiplicand，dataB 為 multiplier。
- 每次循環判斷最低位是否為 1，並執行累加與位移，共進行 32 次運算後輸出乘積。

### Shifter
- 使用五層 Barrel Shifter，每層根據位移量使用 2x1 MUX 控制，共需 160 個 MUX。

### HiLo 暫存器
- 接收乘法器輸出結果的 64-bit 數值，將高 32 位輸出至 HiOut，低 32 位輸出至 LoOut。

### MUX
- 以三元運算子實現，根據控制訊號選擇輸出來源。

### ALU Control
- 根據指令選擇運算模組（如 ALU、乘法器、Shifter 等）並產生對應控制訊號。

### TestBench
- 從檔案讀入測資並驗證模組運作是否正確，配合 ModelSim 產出 Waveform。

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
