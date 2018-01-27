#pragma once

#ifndef CCLIP_NETWORK_H
#define CCLIP_NETWORK_H

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "errorlog.h"

#define SERVER_PORT 6677

#define PRIVATEKEY "key.pem"
#define CERTIFICATE "cert.pem"


using namespace std;

SOCKET create_socket(ofstream& lerr, mutex& mtx_errorlog);
void init_openssl();
SSL_CTX *set_context(ofstream& lerr, mutex& mtx_errorlog);
int accept_client(SOCKET server, SSL_CTX *ctx, SOCKET &client, SSL *&ssl, ofstream& lerr, mutex& mtx_errorlog);
void close_client(SOCKET client, SSL* ssl);
void network_cleanup(SOCKET server, SSL_CTX *ctx);

#endif