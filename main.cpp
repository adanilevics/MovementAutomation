#include "mousemove.h"
#include <Windows.h>

int main() {
    int startX = 100;
    int startY = 100;
    int endX = 500;
    int endY = 500;

    // Define the duration in milliseconds
    int durationMs = 600; // 0.6 seconds

    // Call moveMouseRandomCurved function
    moveMouseRandomCurved(startX, startY, endX, endY, durationMs);

    // Get the current mouse position
    POINT currentPosition1;
    GetCursorPos(&currentPosition1);

    // Move to three other places based on the current mouse position
    moveMouseRandomCurved(currentPosition1.x, currentPosition1.y, 300, 200, durationMs);
    
    GetCursorPos(&currentPosition1); // Recapture the current mouse position
    moveMouseRandomCurved(currentPosition1.x, currentPosition1.y, 700, 400, durationMs);
    Wait(100); // sleep for 100ms (0,1s)

    GetCursorPos(&currentPosition1); // Recapture the current mouse position
    moveMouseRandomCurved(currentPosition1.x, currentPosition1.y, 200, 600, durationMs);
    Wait(100); // sleep for 100ms (0,1s)

    Click(); // click once
    Click(100); // 100ms wait between pressing and releasing the mouse button

    return 0;
}