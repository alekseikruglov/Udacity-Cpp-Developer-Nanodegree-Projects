# Memory Management Chatbot

Udacity C++ Nanodegree Program

## Overview

This is the project for the third course in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213): Memory Management.

<p align="center">
  <img src="./images/gif_out2.gif" title = "Car counting program visualization" alt = "Car counting program visualization" width = "300" />
</p>


The ChatBot code creates a dialogue where users can ask questions about some aspects of memory management in C++. After the knowledge base of the chatbot has been loaded from a text file, a knowledge graph representation is created in computer memory, where chatbot answers represent the graph nodes and user queries represent the graph edges. After a user query has been sent to the chatbot, the Levenshtein distance is used to identify the most probable answer. 

The project focus is to optimize the memory management by using of smart pointers, move semantics, memory ownership and memory allocation.

## Dependencies
* cmake >= 3.11
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* wxWidgets >= 3.0
  * Linux: `sudo apt-get install libwxgtk3.0-dev libwxgtk3.0-0v5-dbg`
  * Mac: There is a [homebrew installation available](https://formulae.brew.sh/formula/wxmac).
  * Installation instructions can be found [here](https://wiki.wxwidgets.org/Install). Some version numbers may need to be changed in instructions to install v3.0 or greater.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./membot`.

## Results


###  Exclusive Ownership 1
In file `chatgui.h` / `chatgui.cpp`, the `_chatLogic` instance is organized as an exclusive resource to class `ChatbotPanelDialog` using `unique smart pointer`. 

###  The Rule Of Five
In file `chatbot.h` / `chatbot.cpp`, the class `ChatBot` complies with the `Rule of Five`, which means: if a class implements any of the following functions, it should implement all of them:
  * destructor
  * copy constructor
  * move constructor
  * copy assignment operator
  * move assignment operator

###  Exclusive Ownership 2
In file `chatlogic.h` / `chatlogic.cpp`, the vector `_nodes` is defined in a way that the instances of `GraphNodes` to which the vector elements refer are exclusively owned by the class `ChatLogic`. The `unique smart pointer` was used to achieve this. 

###  Moving Smart Pointers

`Move Sematic` moves resources from one object to another instead of copying them, which is more memory efficient and is important especially by large data. 

When transferring ownership from class `ChatLogic`, where all instances of `GraphEdge` are created, into instances of `GraphNode`, the `move semantic` was used. 

###  Moving the ChatBot

In file `chatlogic.cpp`, a local `ChatBot` instance is created on the stack at the bottom of function `LoadAnswerGraphFromFile`. Then, the move semantics is used to pass the `ChatBot` instance into the root node. The `ChatLogic` has no ownership relation to the `ChatBot` instance and thus is no longer responsible for memory allocation and deallocation 
