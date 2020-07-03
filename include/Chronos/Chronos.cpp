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


#include "Chronos.h"



Chronos* Chronos::m_instance = nullptr;

Chronos::Chronos() {
    // Do nothing for now
    this->m_processes.clear();
}

Chronos::~Chronos() {
    // Do nothing for now
}

Chronos* Chronos::get_instance() {
    if (m_instance == nullptr){
        m_instance = new Chronos();
    } 
    return m_instance;   
}

long Chronos::find_process(std::string func_name, std::string id) {
    long counter = -1;
    for (unsigned long i = 0; i < m_processes.size(); i++){
        if(m_processes.at(i).get_name().compare(func_name) == 0){
            if(m_processes.at(i).get_unique_id().compare(id) == 0){
                counter = i;
                break;
            }// End of if
        }// End of if
    }// End of for loop
    return counter;
}


void Chronos::aggregate_data() {
    // This function will look through the list of processes, and create another list
    // containing single instances of all the processes. i.e. It will add up all the individual information
    // and create a single entry for every process it finds.
    std::vector<ChronosProcess> aggregate;
    std::list<std::string> functions;
    std::vector<std::string> unique_functions;

    // Create a unique vector storing only the names of the functions being called
    // Convert to a list
    for (ChronosProcess cp: m_processes){
        functions.push_back(cp.get_name());
    }// End of for

    // Ensure there is only one of each function in the list
    functions.sort();
    functions.unique();

    //Convert back to a vector
    for (std::string func_name: functions){
        unique_functions.push_back(func_name);
    }// End of for

    // Aggregate the times based on the number of occurrences of each function
    // NOTE: These for loops take a bit more time
    for(std::string func_name: unique_functions){
        ChronosProcess new_cp = ChronosProcess(func_name);
        bool has_id = false;
        // Cycle through the list of functions found
        for(ChronosProcess cp: m_processes){
            // Only add the time if the processes are the same
            if(cp.get_name().compare(new_cp.get_name()) == 0){  // Are the same
                // Get the ID to use
                if(!has_id){
                    new_cp.set_unique_id(cp.get_unique_id());
                }// end of if

                // Add the functions total time to the ChronosProcess
                new_cp.add_time(cp.get_total_time());
            }
        }// end of for

        // Add the new ChronosProcess to the aggregate
        aggregate.push_back(new_cp);
    }//end of for loop

    // Clean the original processes add the aggregate to the end of the m_processes
    functions.clear();
    unique_functions.clear();
    m_processes.clear();
    for(unsigned long i = 0; i < aggregate.size(); i++){
        m_processes.push_back(aggregate.at(i));
    }//end of for
}


void Chronos::start(std::string func_name, std::string id, bool log) {
    // Only continue should the programmer wish to log the data
    if (log){
        long location = find_process(func_name, id);
        
        if(location >= 0){
            std::chrono::time_point<std::chrono::high_resolution_clock> time = std::chrono::high_resolution_clock::now();
            m_processes.at(location).set_start_time(time);
        }else{
            ChronosProcess cp = ChronosProcess(func_name, id);
            std::chrono::time_point<std::chrono::high_resolution_clock> time = std::chrono::high_resolution_clock::now();
            cp.set_start_time(time);
            m_processes.push_back(cp);
        }
    }// end of if
}

void Chronos::stop(std::string func_name, std::string id, bool log) {
    // Only continue should the programmer wish to log the data
    if (log){
        // Create a new index if it's not found
        long location = find_process(func_name, id);
        if(location >= 0){
            std::chrono::time_point<std::chrono::high_resolution_clock> time = std::chrono::high_resolution_clock::now();
            m_processes.at(location).set_stop_time(time);

            //Calculate the required time
            std::chrono::duration<double> elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>
                                                         (m_processes.at(location).get_stop_time() - m_processes.at(location).get_start_time());
            m_processes.at(location).add_time(elapsed_time.count());
            
        }// Do nothing otherwise
    }// end of if
}


std::string Chronos::get_id() {
    // Use the time since epoch to create a hash value for an ID
    std::string to_return;

    auto now = std::chrono::steady_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::microseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    long timer = epoch.count();
    std::size_t hash_val = std::hash<long>{}(timer);
    long hash_num = static_cast<long>(hash_val);
    to_return = std::to_string(hash_num);

    return to_return;
}


void Chronos::friendly_stop() {
    // Aggregate the found data        
    aggregate_data();

    // Allow for header finding
    ChronosProcess cp;

    // Make the necessary Folder
    namespace fs = std::filesystem;
    std::string profiler_path = "profiler";
    fs::create_directory(profiler_path.c_str());


    // Write a CSV File with the data for later use
    std::ofstream csv_file;
    std::string csv_path = "profiler/ChronosProfile.csv";
    csv_file.open(csv_path.c_str(), std::ios::out);
    if(csv_file.is_open()){
        std::string to_write = cp.get_header_csv() + '\n';
        csv_file << (to_write);
        for(ChronosProcess agg_cp: m_processes){
            to_write = agg_cp.to_csv() + '\n';
            csv_file << (to_write);
        }// end of for
    }else{
        std::string error_string = "Error writing file to: \"" + csv_path+"\"";
        perror(error_string.c_str()); 
    }// end of if else
    csv_file.close();

    // Write a txt File with the data for later use
    std::ofstream txt_file;
    std::string txt_path = "profiler/ChronosProfile.txt";
    txt_file.open(txt_path.c_str(), std::ios::out);
    if(txt_file.is_open()){
        std::string to_write = cp.get_header() + '\n';
        txt_file << (to_write);
        for(ChronosProcess agg_cp: m_processes){
            to_write = agg_cp.to_string() + '\n';
            txt_file << (to_write);
        }// end of for
    }else{
        std::string error_string = "Error writing file to: \"" + txt_path+"\"";
        perror(error_string.c_str()); 
    }// end of if else
    csv_file.close();

}
