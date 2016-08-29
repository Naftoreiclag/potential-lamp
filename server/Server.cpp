/*
   Copyright 2016 James Fong

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "Server.hpp"

#include <iostream>
#include <string>
#include <cassert>

#include "boost/bind.hpp"

namespace gtm {

Server::Server()
: mInitialized(false)
, mSocket(nullptr)
, mServiceThread(nullptr) {
}

Server::~Server() {
    if(mSocket) {
        if(mSocket->is_open()) mSocket->close();
        delete mSocket;
    }
}

void Server::onSocketReceiveFrom(const boost::system::error_code& error, std::size_t numBytesRecv) {
    // mRemoteEndpoint contains the endpoint that just sent us data
    
    if(!error || error == boost::asio::error::message_size) {
        std::cout << std::string(mRecvBuffer.begin(), mRecvBuffer.end()) << std::endl;
        resumeListening();
    }
    
    // Something fatal happened
    else {
        std::cerr << "Big error! " << error.message() << std::endl;
    }
}
void Server::onSocketSendTo(const boost::system::error_code& error, std::size_t numBytesSent) {
    // Do nothing
}

void Server::initialize(uint16_t port) {
    assert(!mInitialized && "Server being initialized again!");
    mPort = port;
    
    mEndpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port);
    mSocket = new boost::asio::ip::udp::socket(mIoService, mEndpoint);
    
    mInitialized = true;
    
    resumeListening();
}

void Server::resumeListening() {
    assert(mInitialized && "Server is uninitialized!");
    assert(mSocket && "Server listening socket is null!");
    mSocket->async_receive_from(boost::asio::buffer(mRecvBuffer), mRemoteEndpoint,
        boost::bind(
            &onSocketReceiveFrom, this, 
            boost::asio::placeholders::error, 
            boost::asio::placeholders::bytes_transferred));
}

void Server::serviceThreadRuntime() {
    mIoService.run();
}

void Server::startServiceThread() {
    assert(mInitialized && "Server is uninitialized!");
    assert(!mServiceThread && "Server service thread already created!");
    
    mServiceThread = new std::thread(serviceThreadRuntime, this);
}

void Server::stopServiceThread() {
    // ???
    // mIoService must have no work to do!
    assert(mServiceThread && "Server service thread is null!");
}


}

