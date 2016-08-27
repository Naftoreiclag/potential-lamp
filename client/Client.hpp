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

#include "boost/asio/io_service.hpp"

#include "ThreadSafeQueue.hpp"

namespace gtm {

class Client {
public:
    class Status {
    public:
        enum State {
            
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
        
        Status(State state);
    private:
        State mState;
        
        std::string
        
        bool isConnected();
    };
    
    boost::asio::io_service mIoService;
    
    Client();
    ~Client();
    
    Status getStatus();

    // Asynchronous, check getStatus()
    void connect(UdpQuery query);
    void disconnect();
    
    void sendPacket(Packet packet);
    bool receivePacket(Packet& packet); // returns true if packet available
};

}

#endif // GTM_CLIENT_HPP
