
<img src="https://raw.githubusercontent.com/faqro/uscor-lang/master/extraRes/UscorLogo.png" height="100"/><img src="https://raw.githubusercontent.com/faqro/uscor-lang/master/extraRes/UscorTitleLogo.png" height="100"/>


An esoteric programming language based on C++ and inspired by Lisp

I was bored. Ignore the exorbitant amount of underscores in code

## How to use
- First make sure that you have the [GNU Compiler Collection](https://gcc.gnu.org/) installed. Windows users can install [MinGW](https://www.mingw-w64.org/). Most Linux distros have g++ preinstalled, otherwise you can install it with `sudo apt-get install g++`. The steps necessary to get the GNU Compiler running on macOS go beyond the scope of this readme, but it should be possible following a tutorial of some kind.
- There are two ways to compile a .usc program.
- You can double click the .exe file for the compiler, which will ask for the address of the .usc file to be compiled
- You can run the compiler as a command line tool. If you do this, you have options:
    - `-i` specifies the input .usc file
	- `-o` specifies the output .exe file
	- `-c` tells the compiler you do not want to delete the .cpp file generated.

## Methods/Functions
| Method/Function  | Parameters | Output | Explanation |
| ------------- | ------------- | ------------- | ------------- |
| comment  | string  | none  | Programming code comment |
| data_declare  | Data Type, Variable Name  | Variable Name  | Defines a new variable with specified data type  |
| <<  | Variable Name, Variable Name or Data Value  | none  | Assigns second parameter value to first parameter |
| + or - or / or *  | Variable Name or Data Value  | Data Value  | Outputs operands applied to parameters  |
| system_io_input  | "console" or ("file" and Fileaccess name) or ("file+" and Fileaccess name) or ("file-" and Fileaccess name) or ("file-=" and Fileaccess name)  | Data Value  | Gets user input from console or a file. "file+" will get a full line. "file-" will read only a character.  "file-=" will read only a character without moving the pointer.  |
| system_io_output  | "console" or ("file" and Fileaccess name)  | Variable Name  | Access output to console or a file  |
| data_type_conversion  | Data Type, Data Type, Variable Name or Data Value  | Data Value  | Convert a value's data type  |
| system_force  | Function/Method  | Same as input  | Force a function or method to be used as an action instead of an expression. Intended for debugging.  |
| system_forcen  | Function/Method  | Same as input  | Force a function or method to be used as an expression instead of an action. Intended for debugging.  |
| string_length  | Variable Name or Data Value  | Data Value  | Get the length of a string  |
| string_substr  | Variable Name or Data Value, Variable Name or Data Value, Variable Name or Data Value  | Data Value  | Return a substring of param0 between positions param1 and param2  |
| string_insert  | Variable Name or Data Value, Variable Name or Data Value, Variable Name or Data Value  | Data Value  | Return string param0 with string param2 inserted at position param1  |
| string_find  | Variable Name or Data Value, Variable Name or Data Value  | Data Value  | Return the index of the first occurrence of param1 in param0  |
| string_escape  | Data Value  | Data Value  | Evaluate the escape characters of input  |
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
| system_exit  | none   | none  | Exit the program or return a global function value if param0 is specified (return "mt" if using an mt function)  |
| system_break  | none   | none  | Break a loop  |
| system_while  | Boolean Value/Name, Functions/Methods...   | none  | Repeat the functions/methods while the boolean value is true  |
| system_for  | Function/Method, Boolean Value/Name, Function/Method, Functions/Methods...   | none  | Run param0 before the loop, then repeat the functions/methods so long as param1 is true. The method in param2 is run after every iteration  |
| = or > or < or >= or <= or != or s=  | Variable Name or Data Value, Variable Name or Data Value  | Boolean Value  | Return a comparison of the two data values. "s=" is a string compare.  |
| data_arr_declare  | Data Type, Variable Name, Variable Name or Data Value...   | Array  | Create an array of type param0, called param1, with size specified by param3+  |
| data_arr_specify  | Variable Name, Variable Name or Data Value...   | Section of Array/Vector/String  | Get the item at index param1 of the array, vector, or string with name param0  |
| data_arrv_declare  | Data Type, Variable Name, Variable Name or Data Value   | Array  | Create a vector of type param0, called param1, with the number of dimensions specified by param2  |
| data_arr_group  | Variable Name or Data Value...   | Array  | Create a static non-variable array with all params as values  |
| data_arrv_size  | Variable Name   | Data Value  | Returns the size of the vector  |
| data_arrv_resize  | Variable Name, Variable Name or Data Value   | none  | Resize a vector. To specify the dimension you must call data_arr_specify  |
| data_arrv_push  | Variable Name, Variable Name or Data Value   | none  | Push an item to a vector with data value specified  |
| data_arrv_pop  | Variable Name   | none  | Remove the last item of a vector  |
| data_arrv_insert  | Variable Name, Variable Name or Data Value, Variable Name or Data Value   | none  | Insert an item in vector at position param1 with value param2  |
| data_arrv_erase  | Variable Name, Variable Name or Data Value, Variable Name or Data Value   | none  | Delete items in a vector at positions between param1 and param2  |
| system_io_file_declare  | "ifs" or "ofs", Fileaccess Name, Variable Name or Data Value (optional)   | none  | Create Fileaccess and open a file from directory param2. "ifs" is read-only, and "ofs" is write-only  |
| system_io_file_close  | "ifs" or "ofs-" or "ofs+", Fileaccess Name   | none  | Close the file provided. "ofs-" will not flush a writeable file, while "ofs+" will. |
| system_io_file_open  | Variable Name or Data Value, Fileaccess Name   | none  | Open a file from directory param2. |
| system_io_file_isopen  | Fileaccess Name   | Boolean Value  | Return whether the fileaccess is holding a file |
| system_io_file_iseof  | Fileaccess Name   | Boolean Value  | Return whether the file has finished reading |
| system_io_file_pointer  | Fileaccess Name   | Data Value  | Returns the current position of the file pointer |
| system_io_file_pointer_move  | Fileaccess Name, 'b' or 'e' or 'c', Data Value or Variable Name   | none  | Move the position of the file pointer, relative to the beginning, end, or current position |
| system_file_copy  | Data Value or Variable Name, Data Value or Variable Name   | none  | Copy a directory and its contents to another directory |
| system_file_remove  | Data Value or Variable Name   | none  | Delete the file or empty folder at a directory |
| system_file_allremove  | Data Value or Variable Name   | none  | Delete a directory including all its contents |
| system_file_createdir  | Data Value or Variable Name   | none  | Create the specified directory |
| system_file_setdir  | Data Value or Variable Name   | none  | Change the current directory |
| system_file_exists  | Data Value or Variable Name   | Boolean Value  | Return whether or not the file or directory exists |
| system_file_tempdir  | none   | Data Value  | Gives a temporary working directory |
| system_file_curdir  | none   | Data Value  | Gives the current directory |
| system_run_cpp  | String Value   | none  | Run C++ code |
| system_run_shell  | String Value or Variable Name   | none  | Run shell commands |
| lib_cinclude  | String Value...   | none  | Add C++ program headers |
| lib_include  | String Value...   | none  | Add Uscor program headers |
| lib_cdefine  | String Value, String Value, String Value   | none  | Define C++ functions. Param0 is the function name, param1 is the C++ reference to the function, and param2 is the C++ code |
| lib_ldefine  | String Value, anything   | none  | Define a local Uscor-replace function. Param0 is function name, and param1 is the replacement. All instances of (param__N) are replaced with corresponding parameters |
| lib_typedefine  | String Value, String Value, String Value   | none  | Define a data type. Param0 is the type name, param1 is the C++ type name, and param2 is the definition of the type name. |
| data_deref  | Variable Name   | Variable Name  | Dereference a data value by pointer |
| data_ref  | Variable Name   | Variable Name  | Reference a data value by pointer |
| require  | Integer Value, Integer Value, Integer Value   | none  | The intended version compiler to build this program. This is helpful in programs where newer versions of Uscor may break compatibility. |

```
Add "Uscor" prefix to all helper functions to prevent code collisions
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
| (data_ref__DATATYPE)  | A reference to another data type  |
| (data_vector__DATATYPE)  | A vector of another data type  |

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
