/**   Copyright 2020 Benrick Smit
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 * 
 *        http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
*/

#pragma once

#include <vector>
#include <list>
#include <chrono>
#include <iostream>
#include <fstream>
#include <ctime>
#include <functional>
#include <filesystem>


#include "ChronosProcess.h"

class Chronos{
   public:
    // Dtor and Initaliser
       ~Chronos();
       static Chronos* get_instance();
       
    // Necessary for Actual operation of class
    void start(std::string func_name, std::string id, bool log = false);
    void stop(std::string func_name, std::string id, bool log = false);

    // Used to get an ID
    std::string get_id();

    // Used to display
    void friendly_stop();

   private:
    // Private Functions not used in singleton
       Chronos();
       Chronos(const Chronos&) = delete;
       Chronos(Chronos&&) = delete;
       Chronos& operator=(const Chronos&) = delete;

       long find_process(std::string func_name, std::string id);

       // Used to aggregate the individual information from the processes vector
       void aggregate_data(); 

       static Chronos* m_instance;

    // Variables for Use
        std::vector<ChronosProcess> m_processes;
};
