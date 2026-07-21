#include <iostream>
#include "../libs/Pzl.h"

int main() {
    int total = 100000;
    int invalid_count = 0;

    for (int i = 1; i <= total; i++) {
        Pzl p = Pzl();
        endwin();

        std::vector<std::vector<int>> v = p.get_vec();

        int flat[9];
        int idx = 0;
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++)
                flat[idx++] = v[r][c];

        int inversions = 0;
        for (int a = 0; a < 9; a++) {
            if (flat[a] == 0) continue;
            for (int b = a + 1; b < 9; b++) {
                if (flat[b] == 0) continue;
                if (flat[a] > flat[b]) inversions++;
            }
        }

        bool valid = (inversions % 2 == 0);
        if (!valid) invalid_count++;

        std::cout << i << " = [";
        for (int j = 0; j < 9; j++) {
            if (flat[j] == 0)
                std::cout << "H";
            else
                std::cout << flat[j];
            if (j < 8) std::cout << ",";
        }
        std::cout << "] -> " << (valid ? "valid" : "invalid") << std::endl;
    }

    std::cout << "---------------------------------" << std::endl;
    std::cout << "Shuffle " << total << " puzzles, and " << invalid_count << " puzzles are unsolvable." << std::endl;

    return 0;
}
