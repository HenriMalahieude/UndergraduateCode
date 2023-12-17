#include "WordLadder.h"

int main(){
    WordLadder w1("./dictionary.txt");

    w1.outputLadder("heart", "wince", "heart.txt");

    WordLadder w2("./dictionary.txt");

    w2.outputLadder("woken", "video", "woken.txt");    

    return 0;
}