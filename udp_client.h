#include <netinet/in.h>
#include <netdb.h>

#include <string>

class UDPClient {
private:
	int sockfd;
    struct sockaddr_in serveraddr;
    struct hostent* server;
public:
	UDPClient(const char* host, const uint16_t &port);
	~UDPClient();
	int send(std::string msg);
};
