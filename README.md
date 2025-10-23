
# 🧠 Quine-McCluskey Minimization Tool

A simple Computer-Aided Design (CAD) tool implemented in C++ that minimizes Boolean functions using the **Quine-McCluskey (QM) Method**. This tool supports minterms and don’t care terms and finds **minimum Sum-of-Products (SOP)** expressions.

---

## 📚 Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Code Structure](#code-structure)
- [Dependencies](#dependencies)
- [Troubleshooting](#troubleshooting)
- [Contributors](#contributors)
- [License](#license)

---

## 🔍 Introduction

This tool is designed to help logic designers simplify Boolean expressions using the Quine-McCluskey algorithm. It handles functions of up to 10 variables and automates:

- Binary conversion of minterms
- Iterative combination of implicants
- Prime implicant extraction
- Essential prime implicant identification
- Minimum SOP discovery using the **Patrick Method**

---

## ✨ Features

- Handles up to 10-variable Boolean functions
- Supports both minterms and don’t cares
- Uses structured vectors and sets for efficient implicant tracking
- Patrick Method for generating all valid SOPs and finding minimal solutions
- Verbose mode for column-wise debugging and Prime Implicant chart printing

---

## 🛠️ Installation

1. **Clone the repository** (if applicable):
   ```bash
   git clone <your-repo-url>
   cd your-project-directory
   ```

2. **Compile the program**:
   ```bash
   g++ -std=c++11 -o qm QM.cpp
   ```

3. **Run the executable**:
   ```bash
   ./qm
   ```

---

## 🧑‍💻 Usage

When you run the program, you will be prompted to enter:

1. **Number of variables (`numVar`)**
2. **List of minterms** (end with `-1`)
3. **List of don’t cares** (end with `-1`)

```text
Please input numVar : 4

Please input minterms : 4 8 10 11 12 15 -1

Please input dontcares : 9 14 -1
```

The program will then display the column-wise simplification process (if verbose), print prime implicant charts, and output all minimum SOPs.

---

## 🧪 Examples

**Test Case 1**
```
numVar = 8
minterms = [0, 2, 5, 6, 7, 8, 10, 12, 13, 14, 15]
dontcares = [255]
```

**Test Case 2**
```
numVar = 9
minterms = [24, 37, 83, 138, 217, 228, 269, 354, 368, 376, 415, 476, 508]
dontcares = [54, 175, 214, 301, 316, 332, 336, 358, 398, 412, 428, 473]
```

**Test Case 3**
```
numVar = 10
minterms = [0, 1, 16, 17, 128, 343, 512, 640, 1023]
dontcares = [341]
```

---

## 🧬 Code Structure

| File      | Description                                               |
|-----------|-----------------------------------------------------------|
| `QM.cpp`  | Main source code containing implementation and main()     |
| `solveQm` | Core function applying Quine-McCluskey and Patrick Method |
| `report.pdf` | Documentation explaining algorithm logic and examples |

---

## 🧩 Dependencies

- C++ Standard Library (STL)
  - `<iostream>`, `<vector>`, `<set>`, `<string>`, `<algorithm>`, `<iomanip>`

No external libraries required.

---

## ⚙️ Troubleshooting

| Problem                              | Solution                                     |
|--------------------------------------|----------------------------------------------|
| Output not showing all SOPs          | Ensure your `numVar` is correct              |
| Redundant SOPs                       | Check don’t cares; avoid overlap with minterms |
| Compilation errors                   | Use `g++` with `-std=c++11` or later         |
| Infinite loop or crash               | Ensure `-1` is entered after inputs          |

---

## 👨‍💻 Contributors

- **Name**: 劉又慈 (Liu Yu-Tzu)  
- **Student ID**: E24116071  
- **Department**: Electrical Engineering (115)  
- **School**: National Cheng Kung University

---

## 📄 License

This project is for academic use. No official license is provided.  
**Contact the contributor for permission to reuse or distribute.**
