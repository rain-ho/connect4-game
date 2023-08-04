#include "CGame.h"
//=====================================================================================================================================

void game_mode0()
{
    int spam;
    Clear();
    cout << "SECRET MODE_EASTER EGG" << endl;
#if defined _WIN32
    system("start https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    rr();
    cout << "PRESS ANY KEY TO CONTINUE";
    cin >> spam;
    return;
#elif defined (__APPLE__)
    system("open https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    this_thread::sleep_for(chrono::milliseconds(3000));
    rr();
    cout << "PRESS ANY KEY TO CONTINUE";
    cin >> spam;
    return;
#endif
}
