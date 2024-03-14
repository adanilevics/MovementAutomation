#include "mousemove.h"
#include <Windows.h>

int main() {

    // defining coordinates
    int startX = 100;
    int startY = 100;
    int endX = 500;
    int endY = 500;

    int durationMs = 600; // 0.6 seconds
    moveMouseRandomCurved(startX, startY, endX, endY, durationMs);

    // get the current mouse position
    POINT currentPosition1;
    GetCursorPos(&currentPosition1);

    // move to three other places based on the current mouse position
    moveMouseRandomCurved(currentPosition1.x, currentPosition1.y, 300, 200, durationMs);
    GetCursorPos(&currentPosition1); // recapture the current mouse position
    moveMouseRandomCurved(currentPosition1.x, currentPosition1.y, 700, 400, durationMs);
    GetCursorPos(&currentPosition1); // recapture the current mouse position
    moveMouseRandomCurved(currentPosition1.x, currentPosition1.y, 200, 600, durationMs);
    
    GetCursorPos(&currentPosition1); 
    moveMouseRandomCurved(currentPosition1.x, currentPosition1.y, 300, 200, 700); // preform movement from current mouse position to 300,200 with a duration of 0.7 ms


    return 0;
}
