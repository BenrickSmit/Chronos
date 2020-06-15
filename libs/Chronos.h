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

/**
 * @author: Benrick Smit
 * @email: metatronicprogramming@hotmail.com
 * @date: 13 June 2020
 * @modified: 13 June 2020
 * 
 * @brief: This class is the main profiler class. It aggregates all the function data it receives and outputs it to two files, one .csv,
 *          the other a .txt, for perusal.
 * 
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
      /**
       * @brief Destroy the Chronos object
       * 
       */
       ~Chronos();
       /**
        * @brief Get the instance object to instantiate the singleton Chronos class
        * 
        * @return Chronos* 
        */
       static Chronos* get_instance();
       
    // Necessary for Actual operation of class
    /**
     * @brief This function starts the profiling for the specified function. It requires three values to be passed to be successful.
     * 
     * @param func_name obtains the functions' name: required use: __PRETTY_FUNCTION__, but any name will do as long as it's consistent
     * @param id a unique string representing something of a primary key to identify the process by
     * @param log used to determine whether the logging should take place or not.
     */
    void start(std::string func_name, std::string id, bool log = false);
    /**
     * @brief This function stops the profiling for the specified function. It requires three values to be passed to be successful.
     * 
     * @param func_name obtains the functions' name: required use: __PRETTY_FUNCTION__, but any name will do as long as it's consistent
     * @param id a unique string representing something of a primary key to identify the process by
     * @param log used to determine whether the logging should take place or not.
     */
    void stop(std::string func_name, std::string id, bool log = false);

    // Used to get an ID
    /**
     * @brief Get the id object which uniquely identifies each process
     * 
     * @return std::string 
     */
    std::string get_id();

    // Used to display
    /**
     * @brief used to output the function information in .csv and .txt format. Additionally, creates a graph if the script is available.
     * 
     */
    void friendly_stop();

   private:
    // Private Functions not used in singleton
       /**
        * @brief Construct a new Chronos object
        * 
        */
       Chronos();
       /**
        * @brief Construct a new Chronos object -- but deleted to ensure singleton status
        * 
        */
       Chronos(const Chronos&) = delete;
       /**
        * @brief Construct a new Chronos object -- but deleted to ensure singleton status
        * 
        */
       Chronos(Chronos&&) = delete;
       /**
        * @brief overloaded operator function -- deleted to ensure singleton status
        * 
        * @return Chronos& 
        */
       Chronos& operator=(const Chronos&) = delete;

       /**
        * @brief This function will determine whether a particular function has been recorded previously or not
        * 
        * @param func_name 
        * @param id 
        * @return long 
        */
       long find_process(std::string func_name, std::string id);

       // Used to aggregate the individual information from the processes vector
       /**
        * @brief Aggregates all the single processes into a form similar to that found in gprof
        * 
        */
       void aggregate_data(); 

      
       static Chronos* m_instance;

    // Variables for Use
        std::vector<ChronosProcess> m_processes;
};
