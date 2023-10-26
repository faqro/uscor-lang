# uscor-lang
A semi-esoteric programming language based on C++ and inspired by Lisp

## Methods/Functions
| Method/Function  | Parameters | Output | Explanation |
| ------------- | ------------- | ------------- | ------------- |
| comment  | string  | none  | Programming code comment |
| data_declare  | Data Type, Variable Name  | Variable Name  | Defines a new variable with specified data type  |
| <<  | Variable Name, Variable Name or Data Value  | none  | Assigns second parameter value to first parameter |
| + or - or / or *  | Variable Name or Data Value  | Data Value  | Outputs operands applied to parameters  |
| (!) system_io_input  | "console" or ("file" and Fileaccess name) or ("file+" and Fileaccess name)  | Data Value  | Gets user input from console or a file. "file+" will get a full line  |
| (!) system_io_output  | "console" or ("file" and Fileaccess name)  | Variable Name  | Access output to console or a file  |
| (!) data_type_conversion  | Data Type, Data Type, Variable Name or Data Value  | Data Value  | Convert a value's data type  |
| (!) string_length  | Variable Name or Data Value  | Data Value  | Get the length of a string  |
| (!) string_substr  | Variable Name or Data Value, Variable Name or Data Value, Variable Name or Data Value  | Data Value  | Return a substring of param0 between positions param1 and param2  |
| (!) math_random_seed  | Variable Name or Data Value  | none  | Seed a random number generator  |
| (!) math_random  | none  | Data Value  | Generate a random number  |
| (!) math_mod  | Variable Name or Data Value, Variable Name or Data Value  | Data Value  | Run a modulo operator on data  |
| (!) math_abs  | Variable Name or Data Value  | Data Value  | Return the absolute value of the parameter  |
| (!) math_max  | Variable Name or Data Value, Variable Name or Data Value  | Data Value  | Return the larger of the two parameters  |
| (!) math_min  | Variable Name or Data Value, Variable Name or Data Value  | Data Value  | Return the smaller of the two parameters  |
| (!) math_cos  | Variable Name or Data Value  | Data Value  | Consine function  |
| (!) math_sin  | Variable Name or Data Value  | Data Value  | Sine function  |
| (!) math_tan  | Variable Name or Data Value  | Data Value  | Tan function  |
| (!) math_acos  | Variable Name or Data Value  | Data Value  | Consine Inverse function  |
| (!) math_asin  | Variable Name or Data Value  | Data Value  | Sine Inverse function  |
| (!) math_atan  | Variable Name or Data Value  | Data Value  | Tan Inverse function  |
| (!) system_or  | Boolean Value/Name, Boolean Value/Name  | Boolean Value  | Return true if one or both of the parameters are true |
| (!) system_and  | Boolean Value/Name, Boolean Value/Name  | Boolean Value  | Return true if both parameters are true |
| (!) system_not  | Boolean Value/Name  | Boolean Value  | Return the opposite of an input boolean |
| (!) system_ifelse  | Boolean Value/Name, Function/Method, Function/Method  | none  | If param0 is true, run the first function. Otherwise, run the second one. |
| (!) system_run  | Functions/Methods  | none  | Run all function paramters  |
| (!) system_cond  | Boolean Value/Name, Variable Name or Data Value, Variable Name or Data Value  | Data Value  | If param0 is true, return param1, otherwise return param2  |
| (!) system_exit  | none   | none  | Exit the program  |
| (!) system_break  | none   | none  | Break a loop  |
| (!) system_while  | Boolean Value/Name, Functions/Methods...   | none  | Repeat the functions/methods while the boolean value is true  |
| (!) system_for  | Function/Method, Boolean Value/Name, Function/Method, Functions/Methods...   | none  | Run param0 before the loop, then repeat the functions/methods so long as param1 is true. The method in param2 is run after every iteration  |
| (!) = or > or < or >= or <= or !=  | Variable Name or Data Value, Variable Name or Data Value  | Boolean Value  | Return a comparison of the two data values  |
| (!) data_arr_declare  | Data Type, Variable Name, Variable Name or Data Value...   | Array  | Create an array of type param0, called param1, with size specified by param3+  |
| (!) data_arr_specify  | Variable Name, Variable Name or Data Value...   | Section of Array/Vector/String  | Get the item at index param1 of the array, vector, or string with name param0  |
| (!) data_arrv_declare  | Data Type, Variable Name, Variable Name or Data Value   | Array  | Create a vector of type param0, called param1, with the number of dimensions specified by param2  |
| (!) data_arrv_size  | Variable Name   | Data Value  | Returns the size of the vector  |
| (!) data_arrv_resize  | Variable Name, Variable Name or Data Value...   | none  | Resize a vector with the dimensions specified  |
| (!) data_arrv_push  | Variable Name, Variable Name or Data Value   | none  | Push an item to a vector with data value specified  |
| (!) data_arrv_pop  | Variable Name   | none  | Remove the last item of a vector  |
| (!) data_arrv_insert  | Variable Name, Variable Name or Data Value, Variable Name or Data Value   | none  | Insert an item in vector at position param1 with value param2  |
| (!) data_arrv_erase  | Variable Name, Variable Name or Data Value, Variable Name or Data Value   | none  | Delete items in a vector at positions between param1 and param2  |
| (!) data_file_declare  | "ifs" or "ofs", Fileaccess Name, Variable Name or Data Value   | none  | Open a file from directory param2. "ifs" is read-only, and "ofs" is write-only  |
| (!) data_file_close  | "ifs" or "ofs-" or "ofs+", Fileaccess Name   | none  | Close the file provided. "ofs-" will not flush a writeable file, while "ofs+" will. |
| (!) system_run_cpp  | String value   | none  | Run C++ code |


Add iterator, esp for files
Add <filesystem>
Add <chrono> and <ctime> (including fps and asynch timer features)
Add live keyboard/mouse input (including mouse position)
Add GUI/canvas

## Data Types
| Type Code  | Data Type |
| ------------- | ------------- |
| int  | Integer  |
| str  | String  |
| bool  | Boolean  |
| float  | Float  |
| double  | Double  |
| char  | Character  |
| char16  | 16bit Character  |
| char32  | 32bit Character  |
| shint  | Short Integer  |
| lint  | Long Integer  |
| llint  | Long Long Integer  |
| ushint  | Unsigned Short Integer  |
| ulint  | Unsigned Long Integer  |
| ullint  | Unsigned Long Long Integer  |
| ldouble  | Long Double  |
| mt  | Void/No data  |
