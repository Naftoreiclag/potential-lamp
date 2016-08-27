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

#ifndef GTM_IPQUERY_HPP
#define GTM_IPQUERY_HPP

#include <string>
#include <stdint.h>

namespace gtm {

struct IpQuery {
    IpQuery(std::string address, uint16_t port);
    ~IpQuery();
    
    std::string address;
    uint16_t port;

};

}

#endif // GTM_IPQUERY_HPP
