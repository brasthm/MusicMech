//
// Created by cyril on 13/05/2022.
//

#ifndef MUSICMECH_SERVER_UDP_PORT_H
#define MUSICMECH_SERVER_UDP_PORT_H

#include <SFML/Network.hpp>
#include <string>
#include <iostream>

#include "main.h"
#include "Utils.h"


class PacketHeader{
private:
    sf::Int32 hash = Utils::hash(SERVER_NAME + SERVER_VERSION);
    inline static PacketHeader *packetHeader;
protected:
    PacketHeader() = default;
public:
    static PacketHeader &getPacketHeader() {
        if(!packetHeader)
            packetHeader = new PacketHeader();
        return *packetHeader;
    }

    PacketHeader(const PacketHeader&) = delete;
    PacketHeader& operator= (const PacketHeader) = delete;

    sf::Int32 getHash() const {
        return hash;
    }

    ~PacketHeader() {
        delete packetHeader;
    };
};

inline sf::Packet& operator <<(sf::Packet& packet, const PacketHeader &packetHeader) {
    return packet << packetHeader.getHash();
};

inline sf::Packet& operator <<(sf::Packet& packet, PacketHeader &packetHeader) {
    return packet << packetHeader.getHash();
};

class UDP_Port {
private:
    sf::UdpSocket socket_;
    sf::Packet recievedPacket_;
    sf::IpAddress recievedIP_;
    unsigned short recievedPort_;
    bool verbose_;
    std::string name_;
public:
    UDP_Port(std::string name);
    explicit UDP_Port(std::string name, int port);
    UDP_Port(std::string name, int port, bool blocking);
    void bind(int port);
    void setBlocking(bool b);
    void setVerbose(bool b);
    sf::IpAddress getSender();
    unsigned short getSenderPort() const;
    sf::Packet &getRecievedPacket();
    inline std::pair<sf::IpAddress, unsigned short> getID() const {
        return {recievedIP_, recievedPort_};
    }

    bool recieve();
    void send(sf::Packet &packet, sf::IpAddress address, unsigned short port);
};


#endif //MUSICMECH_SERVER_UDP_PORT_H
