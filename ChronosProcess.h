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
 * @author: benrick
 * @date: 13 June 2020
 * @modified: 13 June 2020
 * 
 * @brief: This class takes in the information passed from the Chronos class and stores it in a form useful for
 * Chronos profiler. The class will obtain calculate the basic statistics and output them when necessary
 * 
 */ 

#pragma once

#include <iostream>
#include <string>
#include <chrono>

class ChronosProcess  {
	public:
		//ctors and dtors
		ChronosProcess(std::string func_name = "None", std::string u_id = "0000");
		~ChronosProcess();
	
		//Getters and Setters
		//Setters
		void set_max_time(double value);
		void set_min_time(double value);
		void set_total_time(double value);
		void set_mean_time(double value);
		void set_total_calls(double value);
		void set_start_time(std::chrono::time_point<std::chrono::high_resolution_clock> value);
		void set_stop_time(std::chrono::time_point<std::chrono::high_resolution_clock> value);
		void set_unique_id(std::string value);
		
		//Getters
		double get_max_time();
		double get_min_time();
		double get_total_time();
		double get_mean_time();
		double get_total_calls();
		std::chrono::time_point<std::chrono::high_resolution_clock> get_start_time();
		std::chrono::time_point<std::chrono::high_resolution_clock> get_stop_time();
		std::string get_name();
		std::string get_unique_id();
		
		//Basic Operation
		void add_time(double used_time);
		std::string to_string();
		std::string to_csv();
		std::string get_header();
		std::string get_header_csv();


	private: 
		// Function that calculates
		void init(std::string func_name = "None", std::string u_id = "0000");
		
		//Member variables useful for aggregation
		std::string m_calling_function;											// Stores the calling function name
		std::string m_unique_id;												// Saves a unique string for a lookup
		double m_max_time;														// Max time the function was called
		double m_min_time;														// Min time the function was called
		double m_mean_time; 													// Average call duration for the function
		double m_total_time;													// Total time spent on this function
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start; 	// Saves the processes' start time
		std::chrono::time_point<std::chrono::high_resolution_clock> m_stop;  	// Saves the processes' stop time
		long m_total_calls;														// Saves the total number of calls to the function
};