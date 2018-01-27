#include "errorlog.h"
#include "network.h"
#include "message.h"

#include <thread>

int main()
{
	ofstream lerr(ERROR_LOG, ios::app);
	mutex mtx_errorlog;

	//write_errorlog(lerr, mtx_errorlog, "Error log test.");

	SOCKET server;
	SSL_CTX *ctx;

	init_openssl();
	ctx = set_context(lerr, mtx_errorlog);
	server = create_socket(lerr, mtx_errorlog);

	while (true)
	{
		SOCKET client;
		SSL *ssl = nullptr;

		if (accept_client(server, ctx, client, ssl, lerr, mtx_errorlog)) {
			continue;
		}

		new thread(client_login, client, ssl, std::ref(lerr), std::ref(mtx_errorlog));
	}

	close_errorlog(lerr, mtx_errorlog);
	network_cleanup(server, ctx);
}