#include "botball.cc"

int main()
{
    InitBot();
    MoveBot(80, 80, 3000);
    CatchUpObject();
    ChangeDirection(180);
    MoveBot(80, 80, 3000);
    PutDownObject();
}