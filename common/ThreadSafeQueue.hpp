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

#ifndef GTM_THREADSAFEQUEUE_HPP
#define GTM_THREADSAFEQUEUE_HPP

#include <mutex>
#include <deque>

namespace gtm {

template <typename T> class ThreadSafeQueue {
private:
    std::mutex mMutex;
    std::deque<T> mInternal;
    
public:
    ThreadSafeQueue();
    ~ThreadSafeQueue();
    
    void enqueue(T object) {
        std::lock_guard<std::mutex> guard(mMutex);
        mInternal.push_back(object);
    }
    
    // unused
    std::size_t size() {
        std::lock_guard<std::mutex> guard(mMutex);
        return mInternal.size();
    }
    
    bool dequeue(T& returnVal) {
        std::lock_guard<std::mutex> guard(mMutex);
        if(mInternal.size() == 0) {
            return false;
        } else {
            returnVal = mInternal.front();
            mInternal.pop_front();
            return true;
        }
    }
};

}

#endif // GTM_THREADSAFEQUEUE_HPP
