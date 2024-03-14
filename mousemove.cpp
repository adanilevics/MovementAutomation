#include "mousemove.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

void Wait(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void seedRandomGenerator() {
    srand(static_cast<unsigned int>(time(nullptr)));
}

POINT getRandomPointInRange(int minX, int minY, int maxX, int maxY) {
    POINT result;
    result.x = rand() % (maxX - minX + 1) + minX;
    result.y = rand() % (maxY - minY + 1) + minY;
    return result;
}

POINT calculateQuadraticBezierPointWithNoiseAndSmoothing(POINT p0, POINT p1, POINT p2, double t, double noiseFactor) {
    POINT result;
    double noiseX = (rand() % 100 - 50) / 100.0 * noiseFactor;
    double noiseY = (rand() % 100 - 50) / 100.0 * noiseFactor;

    static POINT controlPoint = getRandomPointInRange(p0.x - 50, p0.y - 50, p2.x + 50, p2.y + 50);

    static POINT smoothedControlPoint = controlPoint; 
    smoothedControlPoint.x = 0.99 * smoothedControlPoint.x + 0.01 * noiseX; 
    smoothedControlPoint.y = 0.99 * smoothedControlPoint.y + 0.01 * noiseY;

    double u = 1.0 - t;
    result.x = static_cast<int>(u * u * p0.x + 2 * u * t * smoothedControlPoint.x + t * t * p2.x);
    result.y = static_cast<int>(u * u * p0.y + 2 * u * t * smoothedControlPoint.y + t * t * p2.y);

    return result;
}


void moveMouseRandomCurved(int startX, int startY, int endX, int endY, int durationMs) {
    seedRandomGenerator();

    SetCursorPos(startX, startY);

    // calculate the distance to move
    int dx = endX - startX;
    int dy = endY - startY;
    int steps = std::max(std::abs(dx), std::abs(dy));

    double timeInterval = static_cast<double>(durationMs) / steps;

    // perform curved movement with humanized speed
    for (int i = 0; i <= steps; ++i) {
        double t = static_cast<double>(i) / steps;

        POINT currentPoint = calculateQuadraticBezierPointWithNoiseAndSmoothing({ startX, startY }, { startX, startY }, { endX, endY }, t, 25.0);
        SetCursorPos(currentPoint.x, currentPoint.y);

        int delay = static_cast<int>(timeInterval * (1 + (rand() % 3 - 1) / 10.0)); // Randomly vary the time interval
        Wait(delay);
    }

    SetCursorPos(endX, endY);
}


void Click(int delayBetweenClicksMs) {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));

    if (delayBetweenClicksMs > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayBetweenClicksMs));
    }
}

void moveMouseRandomCurvedClient(int windowX, int windowY, int durationMs) {

    HWND activeWindow = GetForegroundWindow();
    if (activeWindow == NULL) {
        std::cerr << "Failed to get handle to the active window." << std::endl;
    }

    // Convert window coordinates to screen coordinates
    POINT screenPoint = { windowX, windowY };
    ClientToScreen(activeWindow, &screenPoint);

    // Get the current mouse position
    POINT currentPosition;
    GetCursorPos(&currentPosition);

    // Move the mouse from its current position to the specified position within the client area
    moveMouseRandomCurved(currentPosition.x, currentPosition.y, screenPoint.x, screenPoint.y, durationMs);

}