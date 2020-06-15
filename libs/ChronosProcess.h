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

#pragma once

#include <iostream>
#include <string>
#include <chrono>

class ChronosProcess  {
	public:
		//ctors and dtors
		/**
		 * @brief Construct a new Chronos Process object with default values if none are specified
		 * 
		 * @param func_name the name of the process to monitor, can be obtained by __PRETTY_FUNCTION__ if not given a unique name
		 * @param u_id the unique id given to all processes.
		 */
		ChronosProcess(std::string func_name = "None", std::string u_id = "0000");
		/**
		 * @brief Destroy the Chronos Process object
		 * 
		 */
		~ChronosProcess();
	
		//Getters and Setters
		//Setters
		/**
		 * @brief Set the max time object
		 * 
		 * @param value 
		 */
		void set_max_time(double value);
		/**
		 * @brief Set the min time object
		 * 
		 * @param value 
		 */
		void set_min_time(double value);
		/**
		 * @brief Set the total time object
		 * 
		 * @param value 
		 */
		void set_total_time(double value);
		/**
		 * @brief Set the mean time object
		 * 
		 * @param value 
		 */
		void set_mean_time(double value);
		/**
		 * @brief Set the total calls object
		 * 
		 * @param value 
		 */
		void set_total_calls(double value);
		/**
		 * @brief Set the start time object
		 * 
		 * @param value A value obtained from the std::chrono library
		 */
		void set_start_time(std::chrono::time_point<std::chrono::high_resolution_clock> value);
		/**
		 * @brief Set the stop time object
		 * 
		 * @param value A value obtained from the std::chrono library
		 */
		void set_stop_time(std::chrono::time_point<std::chrono::high_resolution_clock> value);
		/**
		 * @brief Set the unique id object
		 * 
		 * @param value 
		 */
		void set_unique_id(std::string value);
		
		//Getters
		/**
		 * @brief Get the max time object
		 * 
		 * @return double 
		 */
		double get_max_time();
		/**
		 * @brief Get the min time object
		 * 
		 * @return double 
		 */
		double get_min_time();
		/**
		 * @brief Get the total time object
		 * 
		 * @return double 
		 */
		double get_total_time();
		/**
		 * @brief Get the mean time object
		 * 
		 * @return double 
		 */
		double get_mean_time();
		/**
		 * @brief Get the total calls object
		 * 
		 * @return double 
		 */
		double get_total_calls();
		/**
		 * @brief Get the start time object
		 * 
		 * @return std::chrono::time_point<std::chrono::high_resolution_clock> 
		 */
		std::chrono::time_point<std::chrono::high_resolution_clock> get_start_time();
		/**
		 * @brief Get the stop time object
		 * 
		 * @return std::chrono::time_point<std::chrono::high_resolution_clock> 
		 */
		std::chrono::time_point<std::chrono::high_resolution_clock> get_stop_time();
		/**
		 * @brief Get the name object
		 * 
		 * @return std::string 
		 */
		std::string get_name();
		/**
		 * @brief Get the unique id object
		 * 
		 * @return std::string 
		 */
		std::string get_unique_id();
		
		//Basic Operation
		/**
		 * @brief A function used to ensure that the total, max, min, and average time a function operates is all calculated accurately.
		 * 
		 * @param used_time 
		 */
		void add_time(double used_time);
		/**
		 * @brief Converts the function data into a format suitable for human processing
		 * 
		 * @return std::string 
		 */
		std::string to_string();
		/**
		 * @brief Converts the function data into a format suitable for csv processing
		 * 
		 * @return std::string 
		 */
		std::string to_csv();
		/**
		 * @brief Get the header data for the human readable text file
		 * 
		 * @return std::string 
		 */
		std::string get_header();
		/**
		 * @brief Get the header data for the csv file
		 * 
		 * @return std::string 
		 */
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