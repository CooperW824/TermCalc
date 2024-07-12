# TermCalc: A simple 4-Function Calculator for the Terminal

I found myself needing a calculator quickly at work, so I built this. Its not super advanced, but it was fun learning FTXUI.

![image](https://github.com/user-attachments/assets/78a4fa35-f5fd-40f0-bb99-4e0187eeefea)


## Installation

You need to have CMake and g++ installed

    sudo apt install cmake build-essentials

Then you can use cmake to build the program

    mkdir build
    cd build
    cmake .. && make -j
    sudo make install

## Using TermCalc

Run:

    calculator
or 

    calc

or 

    termcalc
 to open, and use Ctrl + C to close.

 You can either click the buttons to interact, or you can use the keyboard.
 The "C" key clears the calculator. Number keys add numbers, period adds a decimal, and +-*/ perform operations.

 ## Future plans
1. Documentation
    - I built this in like 3 or 4 hours, there is no docs, I would like to add some
2. Add more functions
   - It would be nice to have more functions like sin, cos, tan, etc.
   
