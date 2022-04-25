In this workshop designed a mini UNIX-like filesystem that supports a few common commands.

Enums were declared indicating type of flag passed while performing the commands. For example passing flags for getting a type of a file system resource, detailed display of a directory or to recursively perform an operation in a directory.

Designed an abstract class named Resource, which is the parent of any file system resource and stores the basic information like name of resource and parent path. It contains pure virtual member functions which are implemented in derived classes: Directory and File. 

Implemented a file system class which contains the resources and allow the user to perform common unix-like commands such as change_directory or get current directory. Directory and files can be added to this class object with operator overloads of += operator. 

Developed other commands in directory class which incorporates finding a resource in the directory with or without recursive flag declared in enum. Similar logic was implemented for removing a resource from directory which was based on rm and rm -r commands. This means an empty directory can be deleted without any issue but a directory containing any content needs to be deleted by setting the recursive flag on. Functionality of detailed and brief display regarding information of the directory was also implemented (just like ls and ls -l commands in Unix). 

Some of the other terminologies used were based on:
a. manage polymorphic objects using the vector container of the STL
b. move a dynamically allocated object into a container
c. code a range-based iteration on the objects in a container
d. report and handle an exception
