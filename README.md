Human-like mouse movement. Preforms a mouse movement from a start position to a target position, with a randomized delay.
Source main.cpp has a use example, with defined start and target positions, and multiple movements stacked with the use of last mouse position to create one flowing movement.


https://github.com/adanilevics/MovementAutomation/assets/110359798/cb3dcd7c-3775-4aab-8269-ae1caf1ec6d9


Create mouse movements by customizing ```main.cpp``` as shown in the examples.


To create an executable with the code within main.

while having the terminal in the directory which contains all the files, g++ compiler needs to be installed and set up ,run these commands :
<br />
<br />```g++ -c -o main.o main.cpp``` 
<br />```g++ -o my_program mousemove.o main.o -lUser32``` 

Replace my_program with the desired name for the .EXE



https://github.com/adanilevics/MovementAutomation/assets/110359798/7f635e55-3a3a-4f67-a42e-b4ae6dfa7f76


