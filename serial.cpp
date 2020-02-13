#include "serial.h"

Serial::Serial() {
    wholeMsg = false;
    c = 'D';
    
    // config termios
    memset(&tio, 0, sizeof(tio));
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

void Serial::tty_init(char* ttyfile, speed_t baud) {
    tty = open(ttyfile, O_RDONLY | O_NONBLOCK);        // O_NONBLOCK might override VMIN and VTIME, so read() may return immediately.
    cfsetospeed(&tio, baud);
    cfsetispeed(&tio, baud);

    tcsetattr(tty, TCSANOW, &tio);
}

char* Serial::readMsg() {
    msg.clear();

    while (!wholeMsg) {
        if (read(tty, &c, 1) > 0) {
            if (c == '\n') {
                break;
            }
            msg.append(&c, 1);
        }
    }

    return (char*)msg.c_str();
}

// bool Serial::isWholeMsg() {
//     if (wholeMsg) {
//         wholeMsg = false;
//         return true;
//     }
//     return false;
// }