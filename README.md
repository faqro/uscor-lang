# Uscor
A semi-esoteric programming language based on C++ and inspired by Lisp

I was bored. Ignore the exorbitant amount of underscores in code

## Methods/Functions
| Method/Function  | Parameters | Output | Explanation |
| ------------- | ------------- | ------------- | ------------- |
| comment  | string  | none  | Programming code comment |
| data_declare  | Data Type, Variable Name  | Variable Name  | Defines a new variable with specified data type  |
| <<  | Variable Name, Variable Name or Data Value  | none  | Assigns second parameter value to first parameter |
| + or - or / or *  | Variable Name or Data Value  | Data Value  | Outputs operands applied to parameters  |
| system_io_input  | "console" or ("file" and Fileaccess name) or ("file+" and Fileaccess name) or ("file-" and Fileaccess name)  | Data Value  | Gets user input from console or a file. "file+" will get a full line. "file-" will read only a character  |
| system_io_output  | "console" or ("file" and Fileaccess name)  | Variable Name  | Access output to console or a file  |
| data_type_conversion  | Data Type, Data Type, Variable Name or Data Value  | Data Value  | Convert a value's data type  |
| system_force  | Function/Method  | Same as input  | Force a function or method to be used as an action instead of an expression. Intended for debugging.  |
| system_forcen  | Function/Method  | Same as input  | Force a function or method to be used as an expression instead of an action. Intended for debugging.  |
| string_length  | Variable Name or Data Value  | Data Value  | Get the length of a string  |
| string_substr  | Variable Name or Data Value, Variable Name or Data Value, Variable Name or Data Value  | Data Value  | Return a substring of param0 between positions param1 and param2  |
| string_find  | Variable Name or Data Value, Variable Name or Data Value  | Data Value  | Return the index of the first occurrence of param1 in param0  |
| math_random_seed  | Variable Name or Data Value  | none  | Seed a random number generator  |
| math_random  | none  | Data Value  | Generate a random number  |
| math_mod  | Variable Name or Data Value, Variable Name or Data Value  | Data Value  | Run a modulo operator on data  |
| math_abs  | Variable Name or Data Value  | Data Value  | Return the absolute value of the parameter  |
| math_max  | Variable Name or Data Value, Variable Name or Data Value  | Data Value  | Return the larger of the two parameters  |
| math_min  | Variable Name or Data Value, Variable Name or Data Value  | Data Value  | Return the smaller of the two parameters  |
| math_cos  | Variable Name or Data Value  | Data Value  | Consine function  |
| math_sin  | Variable Name or Data Value  | Data Value  | Sine function  |
| math_tan  | Variable Name or Data Value  | Data Value  | Tan function  |
| math_acos  | Variable Name or Data Value  | Data Value  | Consine Inverse function  |
| math_asin  | Variable Name or Data Value  | Data Value  | Sine Inverse function  |
| math_atan  | Variable Name or Data Value  | Data Value  | Tan Inverse function  |
| math_pow  | Variable Name or Data Value, Variable Name or Data Value  | Data Value  | Return param0 to the power of param1  |
| math_log  | Variable Name or Data Value, Variable Name or Data Value  | Data Value  | Return Log base param0 of param1  |
| math_pi  | none  | Data Value  | Return pi constant  |
| math_e  | none  | Data Value  | Return euler's constant  |
| math_floor  | Variable Name or Data Value  | Data Value  | Round the input down  |
| math_ceil  | Variable Name or Data Value  | Data Value  | Round the input up  |
| math_round  | Variable Name or Data Value  | Data Value  | Round the input to the nearest integer  |
| system_or  | Boolean Value/Name, Boolean Value/Name  | Boolean Value  | Return true if one or both of the parameters are true |
| system_and  | Boolean Value/Name, Boolean Value/Name  | Boolean Value  | Return true if both parameters are true |
| system_not  | Boolean Value/Name  | Boolean Value  | Return the opposite of an input boolean |
| system_ifelse  | Boolean Value/Name, Function/Method, Function/Method  | none  | If param0 is true, run the first function. Otherwise, run the second one. |
| system_run  | Functions/Methods  | none  | Run all function paramters  |
| system_cond  | Boolean Value/Name, Variable Name or Data Value, Variable Name or Data Value  | Data Value  | If param0 is true, return param1, otherwise return param2  |
| system_exit  | none   | none  | Exit the program  |
| system_break  | none   | none  | Break a loop  |
| system_while  | Boolean Value/Name, Functions/Methods...   | none  | Repeat the functions/methods while the boolean value is true  |
| system_for  | Function/Method, Boolean Value/Name, Function/Method, Functions/Methods...   | none  | Run param0 before the loop, then repeat the functions/methods so long as param1 is true. The method in param2 is run after every iteration  |
| = or > or < or >= or <= or !=  | Variable Name or Data Value, Variable Name or Data Value  | Boolean Value  | Return a comparison of the two data values  |
| (!) data_arr_declare  | Data Type, Variable Name, Variable Name or Data Value...   | Array  | Create an array of type param0, called param1, with size specified by param3+  |
| (!) data_arr_specify  | Variable Name, Variable Name or Data Value...   | Section of Array/Vector/String  | Get the item at index param1 of the array, vector, or string with name param0  |
| (!) data_arrv_declare  | Data Type, Variable Name, Variable Name or Data Value   | Array  | Create a vector of type param0, called param1, with the number of dimensions specified by param2  |
| (!) data_arrv_size  | Variable Name   | Data Value  | Returns the size of the vector  |
| (!) data_arrv_resize  | Variable Name, Variable Name or Data Value...   | none  | Resize a vector with the dimensions specified  |
| (!) data_arrv_push  | Variable Name, Variable Name or Data Value   | none  | Push an item to a vector with data value specified  |
| (!) data_arrv_pop  | Variable Name   | none  | Remove the last item of a vector  |
| (!) data_arrv_insert  | Variable Name, Variable Name or Data Value, Variable Name or Data Value   | none  | Insert an item in vector at position param1 with value param2  |
| (!) data_arrv_erase  | Variable Name, Variable Name or Data Value, Variable Name or Data Value   | none  | Delete items in a vector at positions between param1 and param2  |
| system_io_file_declare  | "ifs" or "ofs", Fileaccess Name, Variable Name or Data Value (optional)   | none  | Create Fileaccess and open a file from directory param2. "ifs" is read-only, and "ofs" is write-only  |
| system_io_file_close  | "ifs" or "ofs-" or "ofs+", Fileaccess Name   | none  | Close the file provided. "ofs-" will not flush a writeable file, while "ofs+" will. |
| system_io_file_open  | Variable Name or Data Value, Fileaccess Name   | none  | Open a file from directory param2. |
| system_io_file_isopen  | Fileaccess Name   | Boolean Value  | Return whether the fileaccess is holding a file |
| system_io_file_iseof  | Fileaccess Name   | Boolean Value  | Return whether the file has finished reading |
| system_run_cpp  | String value   | none  | Run C++ code |

```
Add iterator, esp for files

Add <filesystem>

Add <chrono> and <ctime> (including fps and asynch timer features, and time(NULL) method)

Add live keyboard/mouse input (including mouse position)

Add GUI/canvas
```

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

## How It Works
1. A lexer program runs through the entire program, generating a list of tokens.
    1. Sequences of two consecutive underscores are considered a seperate token (unless between quotation marks)
    2. Regular brackets are considered seperate tokens (unless between quotation marks)
2. A parser program runs through the list of tokens, creating an abstract syntax tree. The tree struct has two values; a data value, and a subtree value. The subtree value is a list of other ASTs.
    1. If the parser runs into an open bracket, it will continue as another branch, and decide that all following tokens will be subtrees of this one.
    2. If the parser runs into a closed bracket, it will exit the current branch, and continue reading in tokens one level lower.
    3. All double underscores are ignored
3. A generator program runs through the AST, and converts it into valid C++ code, recursively starting from the lowest level trees, and working its way back up.
4. The created C++ file is read into a compiler to convert it into an executable file.
