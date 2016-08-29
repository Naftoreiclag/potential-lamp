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

#ifndef GTM_CLIENT_HPP
#define GTM_CLIENT_HPP

#include <string>
#include <stdint.h>
#include <thread>
#include <mutex>

#include "boost/asio.hpp"

#include "ThreadSafeQueue.hpp"
#include "IpQuery.hpp"
#include "Packet.hpp"

namespace gtm {

class Client {
public:
    class Status {
    public:
        enum State {
            
            //
            UNINITIALIZED,
            
            // 
            CONNECTED, // Connection healthy and able to send packets
            
            // Errors, connection suspended
            STREAM_PAUSED, // Server not sending enough packets
            
            // Errors, connection dead
            SERVER_TIMED_OUT, // Spent too long in STATE_PAUSED state
            KICKED, // Forcefully disconnected, has admin-defined message
            NO_CONTACT, // Never received a response during handshaking
            
            // Initialization of connection
            RESOLVING_QUERY, // Until first handshake packet is received from server
            REQUESTING_CONNECTION // In handshake process, cannot yet
        };
        
        Status(State state, std::string msg = "");
        
        bool isConnectionAlive();
        bool isConnectionPaused();
    private:
        State mState;
        
        std::string mMsg;
    };
    
    Client();
    ~Client();
    
    Status getStatus();
    void connect(IpQuery query);
    void disconnect();
    void sendPacket(Packet& packet);
    bool receivePacket(Packet& packet); // returns true if packet available
    
    void startServiceThread();
    void stopServiceThread();
    
    void send(std::string msg);
private:
    std::mutex mStatusMutex;
    Status mStatus;
    
    std::thread* mServiceThread;
    void serviceThreadRuntime();
    
    boost::asio::io_service mIoService;
    boost::asio::ip::udp::socket* mSocket;
    boost::asio::ip::udp::endpoint mServerEndpoint;
};

}

#endif // GTM_CLIENT_HPP
