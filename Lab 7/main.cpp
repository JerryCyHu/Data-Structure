#include <iostream>

int countingSteps(int x, int y){
    static int pathsCounter = 0;
    if (x == 0 && y == 0){
        pathsCounter++;
    } else if(x == 0 && y > 0){
        countingSteps(x, y-1);
    } else if(x > 0 && y == 0){
        countingSteps(x-1, y);
    } else{
        countingSteps(x,y-1);
        countingSteps(x-1,y);
    }
    return pathsCounter;
}

int main() {
    std::cout<<countingSteps(10,10);
    return 0;
}