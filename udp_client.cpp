#include "udp_client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <assert.h>

UDPClient::UDPClient(const char* host, const uint16_t &port) {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sockfd >= 0);

    server = gethostbyname(host);
    assert(server != NULL);

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy(server->h_addr, &serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(port);

}

UDPClient::~UDPClient() {
}

int UDPClient::send(std::string msg) {
    return sendto(sockfd, msg.c_str(), msg.length(), 0,
            (sockaddr*)&serveraddr, sizeof(serveraddr));
}
