#include "window.h"

int main(int argc, char* argv[]) {
    Window window;
    if(window.LoadAssets()) {
        window.Play();
    } else {
        return 1;
    }
    return 0;
}