#include "TCP_Socket.h"

#include <iostream>

TCP_Socket::TCP_Socket()
{
	socket_.setBlocking(false);
	connected_ = false;
	isConnecting_ = false;
}

void TCP_Socket::monitor()
{
	sf::Socket::Status status;

	// Connect

	if (isConnecting_) {
		status = socket_.connect(remoteAddress_, remotePort_);
		if (status == sf::Socket::Done) {
			isConnecting_ = false;
			connected_ = true;
			std::cout << "TCP_SOCKET : Connected " << std::endl;
		}
		if (status == sf::Socket::Error || status == sf::Socket::Disconnected) {
			isConnecting_ = false;
			std::cout << "TCP_SOCKET : Unexpected Error" << std::endl;
		}
	}

	if (connected_) {
		// Sending

		if (!sendingQueue_.empty()) {
			status = socket_.send(sendingQueue_.front());
			if (status == sf::Socket::Done) {
				sf::Packet p = sendingQueue_.front();
				sendingQueue_.pop_front();
				sf::Uint8 state;

				p >> state;
				std::cout << "TCP_SOCKET : Packet Sent (" << (int)state << ")" << std::endl;
			}
			if (status == sf::Socket::Error) {
				std::cout << "TCP_SOCKET : Unexpected Error" << std::endl;
			}
			if (status == sf::Socket::Disconnected) {
				std::cout << "TCP_SOCKET : Socket not connected. Can't send packets anymore." << std::endl;
			}
		}
	}
}

void TCP_Socket::connect(sf::IpAddress address, unsigned int port)
{
	remoteAddress_ = address;
	remotePort_ = port;
	isConnecting_ = true;
}

void TCP_Socket::disconnect()
{
	//socket_.disconnect();
	connected_ = false;
	obsolete_ = true;
}

void TCP_Socket::send(sf::Packet packet)
{
	sendingQueue_.emplace_back(packet);
}

void TCP_Socket::recieve()
{
	// Recived
	sf::Packet recivedPacket;
	sf::Socket::Status status = socket_.receive(recivedPacket);

	if (status == sf::Socket::Done) {
		recivedPackets_.emplace_back(recivedPacket);
	}
	if (status == sf::Socket::NotReady) {
		std::cout << "TCP_SOCKET : Socket not ready. No packet was recieved." << std::endl;
	}
	if (status == sf::Socket::Partial) {
		std::cout << "TCP_SOCKET : Partial Data retrieved. Data is corrupted." << std::endl;
	}
	if (status == sf::Socket::Error) {
		std::cout << "TCP_SOCKET : Unexpected Error." << std::endl;
	}
	if (status == sf::Socket::Disconnected) {
		std::cout << "TCP_SOCKET : Socket not connected. Can't recieve packets anymore." << std::endl;
		obsolete_ = true;
	}
}

sf::Packet TCP_Socket::getRecivedPacket()
{
	if (recivedPackets_.empty()) {
		return sf::Packet();
	}

	sf::Packet ret = recivedPackets_.front();
	recivedPackets_.pop_front();
	return ret;
}

bool TCP_Socket::isReady()
{
	return !recivedPackets_.empty();
}

sf::TcpSocket& TCP_Socket::getSocket()
{
	return socket_;
}

sf::IpAddress TCP_Socket::getRemoteAddress()
{
	return socket_.getRemoteAddress();
}

sf::Uint16 TCP_Socket::getRemotePort()
{
	return socket_.getRemotePort();
}

bool TCP_Socket::isObsolete()
{
	return obsolete_;
}

void TCP_Socket::accept()
{
	connected_ = true;
}
