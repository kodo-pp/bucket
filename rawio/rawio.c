#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

#include "rawio.h"

static struct termios orig_mode;

bool enterRawMode(void) {
    if (tcgetattr(STDIN_FILENO, &orig_mode) == -1) {
        return false;
    }

    struct termios raw_mode = orig_mode;

    /* Set input flags */
    raw_mode.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw_mode.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    raw_mode.c_oflag &= ~(OPOST);
    raw_mode.c_cflag &= ~(CS8);

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_mode) == -1) {
        return false;
    }
    return true;
}

bool exitRawMode(void) {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_mode) == -1) {
        return false;
    }

    return true;
}
