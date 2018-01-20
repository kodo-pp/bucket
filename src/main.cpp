#include <rawio.h>
#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

#define die(reason) do { \
    cerr << "\033[31m" << "Fatal error: " << reason << "\033[0m" << endl; \
    exit(1); \
} while (0)

int main() {
    if (!enterRawMode()) {
        die("unable to enter raw mode");
    }
    atexit(reinterpret_cast <void(*)(void)> (exitRawMode));

    char c;

    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
        cout << "Read byte: " << (int)c << endl;
    }

    if (!exitRawMode()) {
        die("unable to exit raw mode");
    }
}
