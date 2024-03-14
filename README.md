Human-like mouse movement. Preforms a mouse movement from a start position to a target position, with a randomized delay.
Source main.cpp has a use example, with defined start and target positions, and multiple movements stacked with the use of last mouse position to create one flowing movement.


https://github.com/adanilevics/MovementAutomation/assets/110359798/cb3dcd7c-3775-4aab-8269-ae1caf1ec6d9


Create mouse movements by customizing ```main.cpp``` as shown in the examples.

To create an executable with the code within main, run :```g++ -o my_program mousemove.o main.o -lUser32```
while having the terminal in the directory which contains all the files, g++ compiler needs to be installed and set up
