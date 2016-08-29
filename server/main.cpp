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

#include <iostream>
#include <chrono>

#include "boost/asio/io_service.hpp"

#include "Server.hpp"

using namespace gtm;

int main(int argc, char** argv) {
    
    std::cout << "Something server!" << std::endl;
    
    Server server;
    
    server.initialize(13808);
    server.startServiceThread();
    
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    return 0;
}
