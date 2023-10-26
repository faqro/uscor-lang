# uscor-lang
A semi-esoteric programming language based on C++ and inspired by Lisp

## Methods/Functions
| Method/Function  | Parameters | Output | Explanation |
| ------------- | ------------- | ------------- | ------------- |
| comment  | string  | none  | Programming code comment |
| data_declare  | Data Type, Variable Name  | Variable Name  | Defines a new variable with specified data type  |
| <<  | Variable Name, Variable Name or Data Value  | none  | Assigns second parameter value to first parameter |
| + or - or / or *  | Variable Name or Data Value  | Data Value  | Outputs operands applied to parameters  |
| system_io_input  | "console"  | Data Value  | Gets user input from console  |
| system_io_output  | "console"  | Variable Name  | Access output to console  |

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
