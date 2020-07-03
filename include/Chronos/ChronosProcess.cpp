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
 * @brief: This class takes in the information passed from the Chronos class and stores it in a form useful for the
 * Chronos profiler. The class will calculate the basic statistics and output them when necessary
 * 
 */ 


#include "ChronosProcess.h"  


//Ctors and Dtors
ChronosProcess::ChronosProcess(std::string func_name, std::string u_id){
    init(func_name, u_id);
}


ChronosProcess::~ChronosProcess() 
{
    // Do Nothing
}

// Getters and Setters
//Setters
void ChronosProcess::set_max_time(double value) {
    m_max_time = value;
}

void ChronosProcess::set_min_time(double value) {
    m_min_time = value;
}

void ChronosProcess::set_total_time(double value) {
    m_total_time = value;
}

void ChronosProcess::set_mean_time(double value) {
    m_mean_time = value;
}

void ChronosProcess::set_total_calls(double value) 
{
    m_total_calls = value;
}

void ChronosProcess::set_start_time(std::chrono::time_point<std::chrono::high_resolution_clock> value) {
    m_start = value;
}

void ChronosProcess::set_stop_time(std::chrono::time_point<std::chrono::high_resolution_clock> value) {
    m_stop = value;
}

void ChronosProcess::set_unique_id(std::string value) {
    m_unique_id = value;
}



//Getters
double ChronosProcess::get_max_time() {
    return m_max_time;
}

double ChronosProcess::get_min_time() {
    return m_min_time;
}

double ChronosProcess::get_total_time() {
    return m_total_time;
}

double ChronosProcess::get_mean_time() {
    return m_mean_time;
}

double ChronosProcess::get_total_calls() {
    return m_total_calls;
}

std::chrono::time_point<std::chrono::high_resolution_clock> ChronosProcess::get_start_time() {
    return m_start;
}

std::chrono::time_point<std::chrono::high_resolution_clock> ChronosProcess::get_stop_time() {
    return m_stop;
}

std::string ChronosProcess::get_name() {
    return m_calling_function;
}

std::string ChronosProcess::get_unique_id() {
    return m_unique_id;
}



//Basic Functionality
void ChronosProcess::add_time(double used_time) {
    // Determine whether the time is longer than the prev maximum time
    if (used_time >= get_max_time()){
        set_max_time(used_time);
    }
    // Determine whether the time is shorter than the prev minimum time
    if (used_time <= get_min_time()){
        set_min_time(used_time);
    }// end of if
    // Add time to that total time already executed
    set_total_time(get_total_time() + used_time);
    // Increment number of calls to the function
    set_total_calls(get_total_calls() + 1);

    // Create the dependent variable
    set_mean_time(get_total_time() / get_total_calls());
}


std::string ChronosProcess::to_string() {
    //Create a string to return that has all the information necessary for display
    std::string to_return;

    to_return = std::to_string(m_max_time)+"\t\t"+ std::to_string(m_min_time)+"\t\t"+std::to_string(m_mean_time);
    to_return = to_return + "\t\t"+ std::to_string(m_total_calls*1.0f)+"\t\t"+std::to_string(m_total_time)+"\t\t"+m_unique_id+"\t\t"+m_calling_function;
    
    return to_return;
}

std::string ChronosProcess::to_csv() {
    std::string to_return;
    
    to_return = std::to_string(m_max_time)+","+ std::to_string(m_min_time)+","+std::to_string(m_mean_time);
    to_return = to_return + ","+ std::to_string(m_total_calls)+","+std::to_string(m_total_time)+","+m_unique_id+","+m_calling_function;

    return to_return;
}


std::string ChronosProcess::get_header() {
    // Create a header String to return
    std::string to_return;

    to_return = "Max Time\t\tMin Time\t\tMean Time\t\tTotal Calls\t\tTotal Time\t\tHash ID\t\t\tCalling Function";

    return to_return;
}

std::string ChronosProcess::get_header_csv(){
    // Create a header string in csv to return
    std::string to_return;

    to_return = "Max Time,Min Time,Mean Time,Total Calls,Total Time,Hash ID,Calling Function";

    return to_return;
}

//Private Functions
void ChronosProcess::init(std::string func_name, std::string u_id) {
    m_calling_function = func_name;
    m_unique_id = u_id;
    m_max_time = __DBL_MIN__;
    m_min_time = __DBL_MAX__;
    m_mean_time = 0;
    m_total_time = 0;
    m_total_calls = 0;
}
