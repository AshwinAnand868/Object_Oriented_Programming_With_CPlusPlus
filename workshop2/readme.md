This workshop is done to get the difference between the performance of the Move and Copy Semantics in C++. 
It involves reading a huge formatted file and storing that into dynamically allocated array of strings. 
Then in the main file, the contents of that dynamically allocated array can be copied into another array
through and can also be moved depending upon the context.  To check the performance between the move and
copy semantics, I made use std::chrono library classes and in the end it was proved after execution that 
move operations has much less overhead than copy construction in terms of performance of the program.
