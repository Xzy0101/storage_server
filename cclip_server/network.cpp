#include "network.h"

SOCKET create_socket(ofstream& lerr, mutex& mtx_errorlog)
{
	/* Initialize WinSock */
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);    // Winsock version 2.2

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		write_errorlog(lerr, mtx_errorlog, "WSAStartup failed with error: " + err);
		exit(EXIT_FAILURE);
	}


	SOCKET s;
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == SOCKET_ERROR) {
		write_errorlog(lerr, mtx_errorlog, "Unable to create socket");
		exit(EXIT_FAILURE);
	}

	if (::bind(s, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
		write_errorlog(lerr, mtx_errorlog, "Unable to bind");
		exit(EXIT_FAILURE);
	}

	if (listen(s, 1) == SOCKET_ERROR) {
		write_errorlog(lerr, mtx_errorlog, "Unable to listen");
		exit(EXIT_FAILURE);
	}

	return s;
}

void init_openssl()
{
	SSL_load_error_strings();
	OpenSSL_add_ssl_algorithms();
}

char *ossl_err_as_string(void)
{
	BIO *bio = BIO_new(BIO_s_mem());
	ERR_print_errors(bio);
	char *buf = NULL;
	size_t len = BIO_get_mem_data(bio, &buf);
	char *ret = (char *)calloc(1, 1 + len);
	if (ret)
		memcpy(ret, buf, len);
	BIO_free(bio);
	return ret;
}

SSL_CTX *set_context(ofstream& lerr, mutex& mtx_errorlog)
{
	const SSL_METHOD *method;
	SSL_CTX *ctx;

	method = SSLv23_server_method();

	ctx = SSL_CTX_new(method);
	if (!ctx) {
		write_errorlog(lerr, mtx_errorlog, "Unable to create SSL context");
		write_errorlog(lerr, mtx_errorlog, ossl_err_as_string());
		exit(EXIT_FAILURE);
	}

	SSL_CTX_set_ecdh_auto(ctx, 1);

	/* Set the key and cert */
	if (SSL_CTX_use_certificate_file(ctx, CERTIFICATE, SSL_FILETYPE_PEM) <= 0) {
		write_errorlog(lerr, mtx_errorlog, ossl_err_as_string());
		exit(EXIT_FAILURE);
	}

	if (SSL_CTX_use_PrivateKey_file(ctx, PRIVATEKEY, SSL_FILETYPE_PEM) <= 0) {
		write_errorlog(lerr, mtx_errorlog, ossl_err_as_string());
		exit(EXIT_FAILURE);
	}

	return ctx;
}

int accept_client(SOCKET server, SSL_CTX *ctx, SOCKET &client, SSL *&ssl, ofstream& lerr, mutex& mtx_errorlog)
/* return 0 when successed, 1 when failed. client SOCKET and SSL is written to client and ssl */
{
	struct sockaddr_in addr;
	int len = sizeof(addr);

	client = accept(server, (struct sockaddr*)&addr, &len);
	if (client < 0) {
		write_errorlog(lerr, mtx_errorlog, "Unable to accept");
		return EXIT_FAILURE;
	}

	ssl = SSL_new(ctx);
	SSL_set_fd(ssl, client);

	if (SSL_accept(ssl) <= 0) {
		write_errorlog(lerr, mtx_errorlog, ossl_err_as_string());
		close_client(client, ssl);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void close_client(SOCKET client, SSL* ssl)
{
	SSL_free(ssl);
	shutdown(client, SD_BOTH);
	closesocket(client);
}

void network_cleanup(SOCKET server, SSL_CTX *ctx)
{
	SSL_CTX_free(ctx);
	shutdown(server, SD_BOTH);
	closesocket(server);
	WSACleanup();
}