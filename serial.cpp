#include "serial.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h> // needed for memset

Serial::Serial() {
    wholeMsg = false;
    c = 'D';
    
    // config termios
    bzero(&tio, sizeof(tio));
    // memset(&tio, 0, sizeof(tio));
    tio.c_iflag = 0;
    tio.c_oflag = 0;
    tio.c_cflag = CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
    tio.c_lflag = 0;
    tio.c_cc[VMIN] = 1;
    tio.c_cc[VTIME] = 5;
}

Serial::~Serial() {
    close(tty);
}

void Serial::tty_init(const char* ttyfile, const speed_t &baud) {
    tty = open(ttyfile, O_RDONLY | O_NONBLOCK);        // O_NONBLOCK might override VMIN and VTIME, so read() may return immediately.
    cfsetospeed(&tio, baud);
    cfsetispeed(&tio, baud);

    tcsetattr(tty, TCSANOW, &tio);
}

std::string Serial::readMsg() {
    msg.clear();

    while (!wholeMsg) {
        if (read(tty, &c, 1) > 0) {
            if (c == '\n') {
                break;
            }
            msg.append(&c, 1);
        }
    }
    return msg;
}

// bool Serial::isWholeMsg() {
//     if (wholeMsg) {
//         wholeMsg = false;
//         return true;
//     }
//     return false;
// }