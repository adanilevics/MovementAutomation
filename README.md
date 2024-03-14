Create mouse movements by customizing ```main.cpp``` as shown in the examples.


To create an executable with the code within main.

while having the terminal in the directory which contains all the files, g++ compiler needs to be installed and set up 
to ensure that gcc is installed, you can run ```gcc --help```
,run these commands :
<br />
<br />```g++ -c -o main.o main.cpp``` 
<br />```g++ -o my_program mousemove.o main.o -lUser32``` 

Replace my_program with the desired name for the .EXE



https://github.com/adanilevics/MovementAutomation/assets/110359798/0c98b848-c652-4777-9fe3-48c890222f57



Source main.cpp has a use examples, with defined start and target positions, and multiple movements stacked with the use of last mouse position to create one flowing movement.

Human-like mouse movement. Preforms a mouse movement from a start position to a target position, with a randomized delay.
Clicking with a custom delay between holding down the mouse and letting it go.
Wait function to add sleeps wherever.

https://github.com/adanilevics/MovementAutomation/assets/110359798/cb3dcd7c-3775-4aab-8269-ae1caf1ec6d9

Moving within an active window, based on the window client coordinates.

https://github.com/adanilevics/MovementAutomation/assets/110359798/ba5fddf9-d28d-4e9a-913f-b34524d71a79





