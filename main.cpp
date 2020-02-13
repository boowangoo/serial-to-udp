#include <stdlib.h>
#include <stdint.h>

#include "serial.h"
// #include "udp_client.h"

#define DWM1001_BAUD B115200

#define DWM1001_TTY_DEFAULT "/dev/ttyACM0"
#define LE_IP4_DEFAULT "127.0.0.1"
#define LE_PORT_DEFAULT 1234

int main(int argc, void** argv) {
    char* tty;
	char* ip_addr;
	uint16_t port;

    if (argc == 1) {
        tty = DWM1001_TTY_DEFAULT;
        ip_addr = LE_IP4_DEFAULT;
        port = LE_PORT_DEFAULT;
    } else if (argc != 4) {
		printf("usage:\t./rpi-relay <DWM1001 tty> <LE ip_addr> <LE port>\n" \
				"example:\t./rpi-relay /dev/ttyACM0 127.0.0.1 1234\n");
		return -1;
	} else {
        tty = (char*)argv[1];
        ip_addr = (char*)argv[2];
        port = (uint16_t)strtol((char*)argv[3], nullptr, 10);
    }

    Serial ser = Serial();
    ser.tty_init(tty, DWM1001_BAUD);

    // UDPClient client = UDPClient();

    char* msg;
    while (true) {
        msg = ser.readMsg();
        // while(!ser.isWholeMsg()) {}
        // client.send(msg);
        printf("%s\n", msg);
    }

	return 0;
}
