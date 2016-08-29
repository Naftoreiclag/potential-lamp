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

#include "Client.hpp"

namespace gtm {

Client::Status::Status(Client::Status::State state, std::string msg)
: mState(state)
, mMsg(msg) {
}
    
bool Client::Status::isConnectionAlive() {
    return mState == CONNECTED || mState == STREAM_PAUSED;
}

bool Client::Status::isConnectionPaused() {
    return mState == STREAM_PAUSED;
}

Client::Client()
: mStatus(Status::State::UNINITIALIZED) {
}

Client::~Client() {
    if(mSocket) {
        if(mSocket->is_open()) mSocket->close();
        delete mSocket;
    }
}

Client::Status Client::getStatus() {
    std::lock_guard<std::mutex> guard(mStatusMutex);
    return mStatus;
}

void Client::connect(IpQuery serverQuery) {
    boost::asio::ip::udp::resolver resolver(mIoService);
    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), "localhost:13808");
    mServerEndpoint = *resolver.resolve(query);
    
    mSocket = new boost::asio::ip::udp::socket(mIoService);
    mSocket->open(boost::asio::ip::udp::v4());
    
    // Debug
    mStatus = Status(Status::State::CONNECTED);
}
void Client::serviceThreadRuntime() {
    mIoService.run();
}

void Client::startServiceThread() {
    mServiceThread = new std::thread(serviceThreadRuntime, this);
}
void Client::stopServiceThread() {
    // ??
}

void Client::sendPacket(Packet& packet) {
    
}

void Client::send(std::string msg) {
    
}

}

