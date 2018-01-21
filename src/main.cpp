#include <rawio++.hpp>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string>

using namespace std;

#define die(reason) do { \
    cerr << "\033[31m" << "Fatal error: " << reason << "\033[0m" << endl; \
    abort(); \
} while (0)

int main() {
    if (!enterRawMode()) {
        die("unable to enter raw mode");
    }
    atexit(reinterpret_cast <void(*)(void)> (exitRawMode));

    int c = '1';
    while (c != 'q') {
        c = io::readKey();
        io::ArrowKey a = io::arrow(c);
        if (a == io::ArrowKey::none) {
            cout << "Read byte: " << (int)c << io::endl;
        } else {
            switch(a) {
            case io::ArrowKey::up:
                cout << "Pressed key up" << io::endl;
                break;
            case io::ArrowKey::down:
                cout << "Pressed key down" << io::endl;
                break;
            case io::ArrowKey::left:
                cout << "Pressed key left" << io::endl;
                break;
            case io::ArrowKey::right:
                cout << "Pressed key right" << io::endl;
                break;
            }
        }
    }

    cout << "Hello " << io::fgcolor(io::Color::blue) << io::style(io::Style::italic) <<
        "world!" << io::reset() << " ::::::)))))" << io::endl;
    auto termSize = io::getSize();
    cout << "Terminal size:   w = " << termSize.first << ", h = " << termSize.second << io::endl;
    cout << "Press any key to exit..." << io::endl;
    cin.get();
}
