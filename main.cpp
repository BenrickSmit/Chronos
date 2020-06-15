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
 * @brief: This is the main class which gives some function examples and how to use them with the profiler
 * 
 */ 


#include <cstdio>
#include <iostream>

#include "libs/Chronos.h"

#define PROFILER_LOG true

long fibb(long value){
    Chronos *profiler = profiler->get_instance();
    std::string id = profiler->get_id();
    profiler->start(__PRETTY_FUNCTION__, id, PROFILER_LOG);

    if (value < 2){
        profiler->stop(__PRETTY_FUNCTION__, id, PROFILER_LOG);
        return value;
    }else {
        profiler->stop(__PRETTY_FUNCTION__, id, PROFILER_LOG);
        return fibb(value - 1) + fibb(value - 2);
    }//end of if
}//end of fibb

long counter(long count){
    Chronos *profiler = profiler->get_instance();
    std::string id = profiler->get_id();
    profiler->start(__PRETTY_FUNCTION__, id, PROFILER_LOG);
    
    long value = 1;
    for (long i = 1; i < count; i++){
        value *= i;
    }//end of for loop

    profiler->stop(__PRETTY_FUNCTION__, id, PROFILER_LOG);
    return value;
}//end of counter

long factorial(long val){
    Chronos *profiler = profiler->get_instance();
    std::string id = profiler->get_id();
    profiler->start(__PRETTY_FUNCTION__, id, PROFILER_LOG);
    if (val == 1){
        profiler->stop(__PRETTY_FUNCTION__, id, PROFILER_LOG);
        return 1;
    }else{
        profiler->stop(__PRETTY_FUNCTION__, id, PROFILER_LOG);
        return val * factorial(val-1);
    }//end of if else
}//end of factorial

int main(){
    Chronos *profiler = Chronos::get_instance();
    std::string id = profiler->get_id();
    profiler->start(__PRETTY_FUNCTION__, id, PROFILER_LOG);
    
    int num = 10;
    std::cout << std::endl << "Factorial " << num << ": " << factorial(num) << std::endl;
    std::cout << "Fibbonacci Sequence " << num << ": " << fibb(num) << std::endl << std::endl;

    profiler->stop(__PRETTY_FUNCTION__, id, PROFILER_LOG);
    profiler->friendly_stop();
    delete profiler;
    return 0;
}