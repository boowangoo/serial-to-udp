#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h> // needed for memset
#include <string> // needed for memset

class Serial {
private:
	struct termios tio;
    int tty;
	bool wholeMsg;

	char c;
	std::string msg;
public:
	Serial();
	~Serial();
	void tty_init(char* ttyfile, speed_t baud);
	char* readMsg();
	// bool isWholeMsg();
};