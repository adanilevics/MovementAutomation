#include "mousemove.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <vector>

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

    // Calculate the distance to move
    int dx = endX - startX;
    int dy = endY - startY;
    int steps = std::max(std::abs(dx), std::abs(dy));

    // Calculate the time interval for each step
    double timeInterval = static_cast<double>(durationMs) / steps;

    POINT lastPoint = {startX, startY};
    for (int i = 1; i <= steps; ++i) {
        double t = static_cast<double>(i) / steps;

        POINT currentPoint = calculateQuadraticBezierPointWithNoiseAndSmoothing({startX, startY}, {startX, startY}, {endX, endY}, t, 25.0);
        
        SetCursorPos(currentPoint.x, currentPoint.y);

        // Calculate the distance between the last and current points
        int dx = currentPoint.x - lastPoint.x;
        int dy = currentPoint.y - lastPoint.y;
        double distance = std::sqrt(dx * dx + dy * dy);

        // Calculate the time required for this step
        int stepDurationMs = static_cast<int>(distance / steps / timeInterval * durationMs);

        // Wait for the calculated time
        Wait(stepDurationMs);

        lastPoint = currentPoint;
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

// Global variable to store the handles of all instances of the target window
std::vector<HWND> targetWindowInstances;

// Callback function for EnumWindows
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    char windowTitle[256];
    GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
    std::string title = windowTitle;
    std::string targetWindowTitle = reinterpret_cast<const char*>(lParam);
    if (title.find(targetWindowTitle) != std::string::npos) {
        // Add the handle to the list of target window instances
        targetWindowInstances.push_back(hwnd);
    }
    return TRUE; // Continue enumeration
}

// Function to bring the specified window to the foreground by its handle
void bringWindowToForeground(HWND windowHandle) {
    // Bring the window to the foreground
    SetForegroundWindow(windowHandle);
}

// Function to bring the target window instance with the specified index to the foreground
void bringWindowToForegroundByInstance(const char* targetWindowTitle, int instanceNumber) {
    // Enumerate through windows to find all instances of the target window
    targetWindowInstances.clear(); // Clear previous instances
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(targetWindowTitle));

    if (instanceNumber >= 0 && instanceNumber < targetWindowInstances.size()) {
        HWND windowHandle = targetWindowInstances[instanceNumber];
        // Restore the window if it is minimized
        if (IsIconic(windowHandle)) {
            ShowWindow(windowHandle, SW_RESTORE);
        }
        // Bring the window to the foreground
        SetForegroundWindow(windowHandle);
    } else {
        std::cerr << "Invalid instance number." << std::endl;
    }
    Wait(200);
}