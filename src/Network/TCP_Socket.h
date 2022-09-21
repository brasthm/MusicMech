#ifndef MUSICMECH_SERVER_TCP_SOCKET_H
#define MUSICMECH_SERVER_TCP_SOCKET_H


#include <SFML/Network.hpp>
#include <list>

class TCP_Socket {
	sf::TcpSocket socket_;
	sf::IpAddress remoteAddress_;
	unsigned int remotePort_;

	bool isConnecting_, connected_, obsolete_;
	std::list<sf::Packet> sendingQueue_, recivedPackets_;
public:
	TCP_Socket();
	void monitor();
	void connect(sf::IpAddress address, unsigned int port);
	void disconnect();
	void send(sf::Packet packet);
	void recieve();
	sf::Packet getRecivedPacket();
	bool isReady();
	sf::TcpSocket& getSocket();
	sf::IpAddress getRemoteAddress();
	sf::Uint32 getRemotePort();
	bool isObsolete();
	void accept();
};

#endif