#ifndef RAWIO_PLUS_PLUS_HPP
#define RAWIO_PLUS_PLUS_HPP

#include <rawio.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

namespace io {
    enum class Color {
        black,
        red,
        green,
        yellow,
        blue,
        purple,
        cyan,
        light_grey,
    };

    enum class Style {
        bold,
        weak,
        italic,
        underline,
        standout,
        hidden,
        strike,
    };
    static const string endl = "\r\n";
    static const string seqBegin = "\033[";

    static string position(int x, int y) {
        stringstream ss;
        ss << io::seqBegin << y << ';' << x << 'H';
        return ss.str();
    }

    static string _color(Color cl, int target) {
        stringstream ss;
        ss << io::seqBegin;

        int color_code = 0;
        switch (cl) {
        case Color::black:
            color_code = 0;
            break;
        case Color::red:
            color_code = 1;
            break;
        case Color::green:
            color_code = 2;
            break;
        case Color::yellow:
            color_code = 3;
            break;
        case Color::blue:
            color_code = 4;
            break;
        case Color::purple:
            color_code = 5;
            break;
        case Color::cyan:
            color_code = 6;
            break;
        case Color::light_grey:
            color_code = 7;
            break;
        }

        ss << target << color_code << 'm';
        return ss.str();
    }

    static string style(Style sl) {
        stringstream ss;
        ss << io::seqBegin;

        int style_code = 0;
        switch(sl) {
        case Style::bold:
            style_code = 1;
            break;
        case Style::weak:
            style_code = 2;
            break;
        case Style::italic:
            style_code = 3;
            break;
        case Style::underline:
            style_code = 4;
            break;
        case Style::standout:
            style_code = 7;
            break;
        case Style::hidden:
            style_code = 8;
            break;
        case Style::strike:
            style_code = 9;
            break;
        }

        ss << style_code << 'm';
        return ss.str();
    }

    static string reset() {
        stringstream ss;
        ss << io::seqBegin << "0m";
        return ss.str();
    }

    static string fgcolor(Color cl) {
        return _color(cl, 3);
    }
    static string bgcolor(Color cl) {
        return _color(cl, 4);
    }

    static pair <int, int> getSize() {
        int w, h;
        get_term_size(&w, &h);
        return make_pair(w, h);
    }

    static const int KEY_EOF = -1;
    static const int KEY_ARROW = 1 << 15;

    enum class ArrowKey {
        none,
        up,
        down,
        right,
        left,
    };

    ArrowKey arrow(int ch) {
        switch (ch) {
        case 'A' | KEY_ARROW:
            return ArrowKey::up;
        case 'B' | KEY_ARROW:
            return ArrowKey::down;
        case 'C' | KEY_ARROW:
            return ArrowKey::right;
        case 'D' | KEY_ARROW:
            return ArrowKey::left;
        default:
            return ArrowKey::none;
        }
    }

/*
    static int readKey() {
        int _c = getchar();
        if (_c == -1) {
            return KEY_EOF;
        }

        char c = (char)_c;

        if (c == '\033') {
            char seq[3];

            if (read(STDIN_FILENO, &seq[0], 1) != 1) {
                return '\033';
            }
            if (read(STDIN_FILENO, &seq[1], 1) != 1) {
                return '\033';
            }

            if (seq[0] == '[') {
                switch (seq[1]) {
                case 'A': case 'B': case 'C': case 'D':
                    {
                    int k = (int)seq[1] | KEY_ARROW;
                    cout << "AAAAAAAAAA" << io::endl;
                    return k;
                    }
                default:
                    cout << "BBBBBBBB " << (char)seq[1] << io::endl;
                    break;
                }
            } else {
                return '\033';
            }
        }
    }
    */

    // Thanks to https://viewsourcecode.org/snaptoken/kilo/03.rawInputAndOutput.html, step 47
    static int readKey() {
        int nread;
        char c;
        while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
            if (nread == -1 && errno != EAGAIN) abort();
        }
        if (c == '\x1b') {
            char seq[3];
            if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
            if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';
            if (seq[0] == '[') {
                switch (seq[1]) {
                case 'A': case 'B': case 'C': case 'D':
                    return seq[1] | KEY_ARROW;
                }
            }
            return '\x1b';
        } else {
            return c;
        }
    }
}

#endif /* end of include guard: RAWIO_PLUS_PLUS_HPP */
