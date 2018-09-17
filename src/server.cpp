#include "./server.h"

void Server::setup()
{
	int status;

	struct addrinfo hints, *res;
	int yes = 1;

	Util::printServer("Initiating network server setup...");

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if((status = getaddrinfo(NULL, "5555", &hints, &res)) != 0)
	{
		std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
		return;
	}

	this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(this->sockfd < 0)
	{
		std::cerr << "Error creating socket!" << std::endl;
		perror("socket");
		return;
	}

	status = setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

	if(status < 0)
	{
		std::cerr << "Couldn't set socket options!" << std::endl;
		perror("setsockopt");
		return;
	}

	status = bind(this->sockfd, res->ai_addr, res->ai_addrlen);

	if(status != 0)
	{
		std::cerr << "Error binding socket!" << std::endl;
		perror("bind");
		return;
	}


	status = listen(this->sockfd, MAX_PLAYERS);
	Util::printServer("Server setup complete.");
	Util::printServer("Listening on port 5555.");

	if(this->encrypted)
	{
		this->setupTLS();
	}

	this->acceptConnections();
}

void Server::acceptConnections()
{
	int clientfd;
	socklen_t len;
	//struct sockaddr_storage client_addr;
	struct sockaddr_in client_addr;
	int status;
	len = sizeof(client_addr);

	while((clientfd = accept(this->sockfd, (struct sockaddr *)&client_addr, &len)))
	{
		if(clientfd < 0)
		{
			std::cerr << "Error accepting connection!" << std::endl;
			std::cerr << "clientfd = " << clientfd << std::endl;
			perror("accept");
		}
		else
		{
			std::stringstream msg;
			msg << "Accepting new connection from client file descriptor " << clientfd;
			Util::printServer(msg.str());
			pthread_t thread_id;
			status = pthread_create(&thread_id, NULL, &Nanny::greetPlayer, (void *)&clientfd);

			if(status < 0)
			{
				std::cerr << "Error creating thread for new connection!" << std::endl;
				perror("pthread");
			}
		}
	}

}

void Server::setupTLS()
{
	SSL_load_error_strings();
	ERR_load_BIO_strings();
	OpenSSL_add_all_algorithms();


}

int Server::getPort()
{
	return this->port;
}

ErrorCode Server::setPort(int p)
{
	if(port <= 0)
	{
		Util::printError("Invalid port supplied for server.");
		return ERROR_INVALID_PORT;
	}

	this->port = p;
	return SUCCESS;
}

ErrorCode Server::setEncryption(bool option)
{
	this->encrypted = option;
	return SUCCESS;
}
