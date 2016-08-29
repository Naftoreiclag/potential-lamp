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

#ifndef GTM_SERVER_HPP
#define GTM_SERVER_HPP

#include <stdint.h>
#include <mutex>
#include <thread>

#include "boost/asio.hpp"
#include "boost/array.hpp"

namespace gtm {

class Server {
private:
    // filled by boost::asio and read by these two methods
    boost::asio::ip::udp::endpoint mRemoteEndpoint;
    boost::array<char, 1024> mRecvBuffer;
    
    void onSocketReceiveFrom(const boost::system::error_code& error, std::size_t numBytesRecv);
    void onSocketSendTo(const boost::system::error_code& error, std::size_t numBytesSent);
    
    // After onSocketReceiveFrom is called, then listening stops; this method is then immediately called to resume listening
    void resumeListening();
    
    boost::asio::io_service mIoService;
    boost::asio::ip::udp::socket* mSocket;
    boost::asio::ip::udp::endpoint mEndpoint;
    
    bool mInitialized;
    
    uint8_t mPort;
    
    std::thread* mServiceThread;
    void serviceThreadRuntime();
    
public:
    Server();
    ~Server();
    
    void initialize(uint16_t port);
    
    void startServiceThread();
    void stopServiceThread();
    
};

}

#endif // GTM_SERVER_HPP
