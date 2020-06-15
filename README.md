# Chronos
Chronos is an easy to use profiler which gives you the ability to manually test your functions. It is not as robust and detailed as the gprof or valgrind profilers, but does its job well.

Chronos allows you to manually select a list of functions to test while giving you the number of times the function was called and the time it took the functions to complete their execution.

Should you have python installed, the class will also automatically create a simple graph detailing where most of your time was spent in the program.

# Instructions
As with many simple programs, Chronos needs to be imported. Both the script and the libs folders need to be imported. The Chronos and ChronosProcess files can be copied in your own third-party library folder. The Script folder, however, should be in the same level as your third-party library folder -- to ensure the profiler can reach the script. The script folder isn't necessary, as it will not hault the flow of the program, but without the script folder, you'll be unable to obtain a simple graph of the functions and their times.

To start off, the following must be written into your <coding>int main()</coding> function.
    <coding>
        #include "libs/Chronos.h"

        #define PROFILER_LOG true

        int main(){
            Chronos* profiler = profiler->get_instance();
            profiler->start(__PRETTY_FUNCTION__, profiler->get_id(), PROFILER_LOG);


            profiler->stop(__PRETTY_FUNCTION__, profiler->get_id(), PROFILER_LOG);
            profiler->friendly_stop();
            return 0;
        }
    </coding>

The above will ensure there is a profile for your first function, while initialising the profiler to track the entire program's execution time.

The execution is simple: you create a pointer to the profiler, which you start with the <coding>profiler->start(...)</coding> command. You stop the profiler with the <coding>profiler->stop(...)</coding> command. The <coding>profiler->friendly_stop()</coding> function is only used at the end of the main function, to tidy up the gathered data and save it to files.

The other preprocessor command <coding>__PRETTY_FUNCTION__</coding> is used to find the function's name while giving as much information about it as possible, while <coding>profiler->get_id()</coding> obtains a unique id for the specific function you are profiling. Each function will have a unique ID by which it can be identified. Do note: __PRETTY_FUNCTION__ is not necessary, any string to identify the function will be acceptable, as long as you stay consistent.

For any additional function you want to test, you just do the same as you did in the main function. The crux is, that you need to ensure you add in the <coding>profiler->stop(...)</coding> before all the program's exit points. It can get messy, but that's why there is the option of turning off the profiler's tracking by using the PROFILER_LOG preprocessor command.

To ensure that a simple, non-recursive function is properly profiled, use the following example as reference:
    <coding>
        #define PROFILER_LOG true
        
        //... More code

        void function(std::string value){
            Chronos* profiler = profiler->get_instance();
            profiler->start(__PRETTY_FUNCTION__, profiler->get_id(), PROFILER_LOG);

            // Do something

            profiler->stop(__PRETTY_FUNCTION__, profiler->get_id(), PROFILER_LOG);
        }
    </coding>

To ensure that a recursive function is properly profiled, use the following example as reference
    <coding>
        #define PROFILER_LOG true
        //... More code

        long function(long value){
            if(value == 1){
                profiler->stop(__PRETTY_FUNCTION__, profiler->get_id(), PROFILER_LOG);
                return 1;
            }else{
                profiler->start(__PRETTY_FUNCTION__, profiler->get_id(), PROFILER_LOG);
                return value + function(value-1);
            }
        }
    </coding>

# License
This software is licensed under the [Apache 2.0 License](LICENSE)

# Contributions
Should you have any additional feedback on the application, please feel free to contact me, or to report a bug.