# 8-Puzzle Shuffle Test

## Compile

```bash
bash compile_test.sh
```

## Run

```bash
./run_test
```

---

## Understanding 8-Puzzle Solvability: The Mathematics of Inversions

When you randomly shuffle the tiles of an 8-Puzzle, there is a mathematical certainty that exactly **50% of the possible initial states are unsolvable**. This is not a limitation of the algorithm attempting to solve it, but rather a fundamental mathematical property of the puzzle itself. 

The solvability of a given 8-puzzle state is determined by counting its **inversions**. 

### What is an Inversion?
If we represent the puzzle tiles as a single 1D array (reading from left to right, top to bottom) and ignore the blank space, an "inversion" occurs whenever a larger number precedes a smaller number in that sequence.

*   If the total number of inversions is **Even**, the puzzle is **Solvable**.
*   If the total number of inversions is **Odd**, the puzzle is **Unsolvable**.

---

### Example 1: The Simplest Unsolvable State

This is the classic example created by taking a solved puzzle and swapping just the last two tiles (7 and 8).

| 1 | 2 | 3 |
|:-:|:-:|:-:|
| 4 | 5 | 6 |
| 8 | 7 |   |

**Inversion Calculation:**
Sequence (ignoring the blank): `1, 2, 3, 4, 5, 6, 8, 7`

*   `1, 2, 3, 4, 5, 6`: Have 0 numbers smaller than them to their right.
*   `8`: Has **1** number smaller than it to its right (`7`).
*   `7`: Has 0 numbers smaller than it to its right.

**Total Inversions:** `0 + 0 + 0 + 0 + 0 + 0 + 1 + 0 = 1`
Since **1 is an Odd number**, this puzzle cannot be solved.

---

### Example 2: A Complex Unsolvable State

Here is a more randomized, highly shuffled state that might look solvable at first glance, but is mathematically impossible to complete.

| 8 | 1 | 2 |
|:-:|:-:|:-:|
| 4 | 3 | 7 |
| 6 | 5 |   |

**Inversion Calculation:**
Sequence (ignoring the blank): `8, 1, 2, 4, 3, 7, 6, 5`

Let's count how many smaller numbers appear *after* each number:
*   **8**: `1, 2, 4, 3, 7, 6, 5` (7 numbers are smaller) -> **7 inversions**
*   **1**: None -> **0 inversions**
*   **2**: None -> **0 inversions**
*   **4**: `3` (1 number is smaller) -> **1 inversion**
*   **3**: None -> **0 inversions**
*   **7**: `6, 5` (2 numbers are smaller) -> **2 inversions**
*   **6**: `5` (1 number is smaller) -> **1 inversion**
*   **5**: None -> **0 inversions**

**Total Inversions:** `7 + 0 + 0 + 1 + 0 + 2 + 1 + 0 = 11`
Since **11 is an Odd number**, this highly shuffled state is completely unsolvable.