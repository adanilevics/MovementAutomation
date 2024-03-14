#include <Windows.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

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

        int delay = static_cast<int>(timeInterval * (1 + (rand() % 3 - 1) / 10.0)); // randomly vary the time interval
        Sleep(delay);
    }

    SetCursorPos(endX, endY);
}

int main() {

    // define start and end coordinates (if needed)
    int startX = 100;
    int startY = 100;
    int endX = 500;
    int endY = 500;

    // define the duration in milliseconds
    int durationMs = 400; // 0.4 seconds
    // duration is randomized, but randomize it anyway before passing it

    moveMouseRandomCurved(startX, startY, endX, endY, durationMs);

    // Get the current mouse position
    POINT currentPosition1;
    GetCursorPos(&currentPosition1);

    // Move to three other places based on the current mouse position
    moveMouseRandomCurved(currentPosition1.x, currentPosition1.y, 300, 200, durationMs);
    GetCursorPos(&currentPosition1); // recapture the current mouse position
    moveMouseRandomCurved(currentPosition1.x, currentPosition1.y, 700, 400, durationMs);
    GetCursorPos(&currentPosition1); // recapture the current mouse position
    moveMouseRandomCurved(currentPosition1.x, currentPosition1.y, 200, 600, durationMs);

    // for humanlike movement, randomize endx and endy (target position), while
    // ensuring that the randomized target position still achieves the goal

    return 0;
}
