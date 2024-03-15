Create your own mouse automation program by customizing ```main.cpp``` , ```main.cpp``` has examples of how to use all the functions within it.


To create an executable from the code written in ```main.cpp```:

Open the terminal in the directory which contains all the files ,g++ compiler needs to be installed and set up 
,to ensure that gcc is installed, you can run ```gcc --help```
<br /> <br />If gcc is installed, you can to compile main.cpp to an .exe with these two commands :
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

<br /><br /><br /><br />


Moving within an active window, based on the window client coordinates.

https://github.com/adanilevics/MovementAutomation/assets/110359798/ba5fddf9-d28d-4e9a-913f-b34524d71a79

<br /><br /><br /><br />


Switching between multiple windows to move mouse in the same window based coordinates.

https://github.com/adanilevics/MovementAutomation/assets/110359798/405b7148-73d2-4f12-ae3b-c17e753eb9b1



