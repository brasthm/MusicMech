//
// Created by cyril on 13/05/2022.
//

#include "UDP_Port.h"
#include <iostream>
#include <utility>


UDP_Port::UDP_Port(std::string name){
    verbose_ = false;
    recievedPort_ = 0;
    name_ = std::move(name);
}

UDP_Port::UDP_Port(std::string name, int port) {
    verbose_ = false;
    recievedPort_ = 0;
    name_ = std::move(name);
    bind(port);
}

UDP_Port::UDP_Port(std::string name, int port, bool blocking) {
    verbose_ = false;
    recievedPort_ = 0;
    name_ = std::move(name);
    bind(port);
    setBlocking(blocking);
}

void UDP_Port::bind(int port) {
    socket_.bind(port);

    if(verbose_)
        std::cout << "Port " << name_ << "  : " << "set PORT to " << socket_.getLocalPort() << std::endl;
}

void UDP_Port::setBlocking(bool b) {
    socket_.setBlocking(b);

    if(verbose_) {
        std::cout << "Port " << name_ << "  : " << "set BLOCKING to ";
        if(b) std::cout << "TRUE";
        else std::cout << "FALSE";
        std::cout << std::endl;
    }
}

void UDP_Port::setVerbose(bool b) {

    if(verbose_) {
        std::cout << "Port " << name_ << "  : " << "set VERBOSE to ";
        if(b) std::cout << "TRUE";
        else std::cout << "FALSE";
        std::cout << std::endl;
    }


    verbose_ = b;

    if(verbose_) {
        std::cout << "Port " << name_ << "  : " << "set VERBOSE to ";
        if(b) std::cout << "TRUE";
        else std::cout << "FALSE";
        std::cout << std::endl;
    }
}

unsigned short UDP_Port::getPort()
{
    return socket_.getLocalPort();
}

bool UDP_Port::recieve() {
    recievedPacket_.clear();
    if(socket_.isBlocking()){
        sf::SocketSelector selector;
        selector.add(socket_);
        if (selector.wait(sf::seconds(TIMOUT_TIME)))
        {
            sf::Socket::Status status = socket_.receive(recievedPacket_, recievedIP_, recievedPort_);
            if (status == sf::Socket::Done) {
                sf::Int32 hash;
                if(recievedPacket_ >> hash) {
                    if(hash == PacketHeader::getPacketHeader().getHash()) {
                        if(verbose_)
                            std::cout << "Port " << name_ << "  : Packet recieved from " << recievedIP_ << "(" << recievedPort_ << ")" << std::endl;
                        return true;
                    }
                    else
                        std::cout << "Port " << name_ << "  : Wrong hash" << std::endl;
                }
                else
                    std::cout << "Port " << name_ << "  : No hash" << std::endl;
            }
            else {
                if (status == sf::Socket::Partial) {
                    std::cout << "Port " << name_ << "  : Partial Data" << std::endl;
                }
                if (status == sf::Socket::Disconnected) {
                    std::cout << "Port " << name_ << "  : Disconnected" << std::endl;
                }
                if (status == sf::Socket::NotReady) {
                    std::cout << "Port " << name_ << "  : Not Ready" << std::endl;
                }
                if (status == sf::Socket::Error) {
                    std::cout << "Port " << name_ << "  : Unexpected Error" << std::endl;
                }
            }
        }
        else {
            std::cout << "Port " << name_ << "  : Request timed out" << std::endl;
        }
    }
    else {
        if (socket_.receive(recievedPacket_, recievedIP_, recievedPort_) == sf::Socket::Done) {
            sf::Int32 hash;
            if(recievedPacket_ >> hash) {
                if(hash == PacketHeader::getPacketHeader().getHash()) {
                    if(verbose_)
                        std::cout << "Port " << name_ << "  : Packet recieved from " << recievedIP_ << "(" << recievedPort_ << ")" << std::endl;
                    return true;
                }
            }
        }
    }

    return false;
}

sf::IpAddress UDP_Port::getSender() {
    return recievedIP_;
}

unsigned short UDP_Port::getSenderPort() const {
    return recievedPort_;
}

sf::Packet &UDP_Port::getRecievedPacket() {
    if (!recievedPacket_)
        std::cout << "ERROR Port " << name_ << "  : Packet corrupted" << std::endl;
    if(recievedPacket_.endOfPacket())
        std::cout << "ERROR Port " << name_ << "  : End of packet reached" << std::endl;
    return recievedPacket_;
}

bool UDP_Port::send(sf::Packet &packet, sf::IpAddress address, unsigned short port) {

    sf::Packet sendPacket;

    const void* data = packet.getData();
    size_t len = packet.getDataSize();
    sendPacket << PacketHeader::getPacketHeader();
    sendPacket.append(data, len);

    if(socket_.send(sendPacket, address, port) == sf::Socket::Done) {
        if(verbose_)
            std::cout << "Port " << name_ << "  : Packet of size " <<
                      len << " sent to " << address << "(" << port << ")" << std::endl;
    }
    else {
        if(verbose_)
            std::cout << "Port " << name_ << "  : Packet of size " <<
                      len << " count not be sent to " << address << "(" << port << ")" << std::endl;
        return false;
    }

    return true;
}

bool UDP_Port::valid()
{
    return recievedPacket_;
}

sf::UdpSocket& UDP_Port::getSocket()
{
    return socket_;
}
