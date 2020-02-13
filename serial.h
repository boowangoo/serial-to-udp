#include <termios.h>
#include <string>

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
	void tty_init(const char* ttyfile, const speed_t &baud);
	std::string readMsg();
	// bool isWholeMsg();
};
