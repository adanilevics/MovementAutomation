Create your own mouse automation program by customizing ```main.cpp``` , ```main.cpp``` has examples of how to use all the functions within it.

### Compiling and creating an executable

To create an executable from the code written in ```main.cpp```:

Open the terminal in the directory which contains all the files. <br />
(g++ compiler needs to be installed and set up. To ensure that gcc is installed, you can run ```gcc --help```)
<br /> <br />If gcc is installed, you can to compile main.cpp to an .exe with these two commands :
<br />
<br />```g++ -c -o main.o main.cpp``` 
<br />```g++ -o my_program mousemove.cpp main.cpp -lUser32 -lgdi32``` <br />
Replace my_program with the desired name for the .EXE

### Troubleshooting note

If you are having trouble compiling, running the command ```g++ -c mousemove.cpp -o mousemove.o``` could resolve the issue
<br /> Otherwise ,ensure that gcc is correctly installed and set up.
<br />
<br />

## Moving the mouse

Move the mouse using a random, curved path from the specified start coordinates, to the specified end coordinates  on the screen over the given duration <br />
```moveMouseRandomCurved(int startX, int startY, int endX, int endY, int durationMs); ```  <br />
<br />
```moveMouseRandomCurved(200, 200, 400, 400, 5000);``` <br />
Example : Move the mouse from (200,200) to (400,400) on the screen over a duration of 5000ms, aka 5 seconds<br />
<br/>
<br />

## Sleep

```Wait(int milliseconds);```  <br />
Wait or sleep for the specified amount in ms  <br />
<br />
```Wait(2000);``` <br />
Example : waits for 2000ms, aka 2 seconds<br />
<br />
<br />

## Click

```Click(int delayBetweenClicksMs = 0);```   <br />
Click (press the mouse button and let go) with a option to specify the amount of time between pressing and letting go the mouse<br />
<br />
```Click(100);``` <br />
Example : Click, with the delay between pressing the mouse and letting it go being 100ms, aka 0.1s<br />
<br />
<br />

## Moving the mouse within an active window

```moveMouseRandomCurvedClient(int windowX, int windowY, int durationMs);```   <br />
Move the mouse using a random, curved path from the current mouse location, to the specified coordinates within a window/client<br />
<br />
```moveMouseRandomCurvedClient(100, 100, 1500);``` <br />
Example : Move the mouse to the coordinates (100,100) in the window that is currently active, over a period of 1500ms, aka 1.5s<br />
<br />
<br />

## Setting a window as active

```bringWindowToForegroundByInstance(const char* targetWindowTitle, int instanceNumber);``` <br />
Brings the specified window out of being minimized (if it is), and sets it as the active window. If using multiple windows with the same name, then instance numbers can be used to navigate. The first window is instanceNumer 0, second is instanceNumber 1, third is instanceNumer 2, ect. instanceNumer is 0-index.<br />
<br />
Context : Assume we have two windows of task manager open, and we first want to set the first one as active, then the second.
<br/>
```bringWindowToForegroundByInstance("Task Manager", 0);``` <br />
```Wait(200);``` <br />
```bringWindowToForegroundByInstance("Task Manager", 1);``` <br />
Example : Brings the 1st instance Task manager out of being minimized (if its minimized), and sets it as the currently active window, then does the same to a 2nd instance of task manager after waiting for 0.s2<br />
<br />
Window names are without their file extension, without .exe or other
<br />
If you are unsure of the window name, have a look at the open processes in task manager and simply use their name

<br />
<br />

## Demo

Creating an executable from the main.cpp code

https://github.com/adanilevics/MovementAutomation/assets/110359798/0c98b848-c652-4777-9fe3-48c890222f57

<br/> <br/>
Moving the mouse

https://github.com/adanilevics/MovementAutomation/assets/110359798/9da111e8-9eaf-4a01-930c-7103378bce3b


<br /><br /><br /><br />


Moving within an active window, based on the window client coordinates.

https://github.com/adanilevics/MovementAutomation/assets/110359798/ba5fddf9-d28d-4e9a-913f-b34524d71a79

<br /><br /><br /><br />


Switching between multiple windows to move mouse in the same window based coordinates.

https://github.com/adanilevics/MovementAutomation/assets/110359798/40258d20-513f-4911-b5e5-768d6c6eaa21




