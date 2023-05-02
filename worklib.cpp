#include"worklib.h"


void playermove(Sprite& player, Vector2f& moveRec)
{
    player.move(moveRec);
    Vector2f pos = player.getPosition();
    if (pos.x > 1100) player.setPosition(1100, pos.y);
    if (pos.x < 50) player.setPosition(50, pos.y);
    if (pos.y > 660) player.setPosition(pos.x, 660);
    if (pos.y < 110) player.setPosition(pos.x, 110);

    if ((pos.x > 1100) && (pos.y < 110)) player.setPosition(1100, 110);
    if ((pos.x > 1100) && (pos.y > 660)) player.setPosition(1100, 660);
    if ((pos.x < 50) && (pos.y < 110)) player.setPosition(50, 110);
    if ((pos.x < 50) && (pos.y > 660)) player.setPosition(50, 660);
}

void playeranim(Sprite& player, FrameAnim& FramePlAnim, int traffic)
{
    FramePlAnim.Frame += FramePlAnim.Step;
    player.setTextureRect(IntRect(0, FramePlAnim.Frame, 90, 90));

    if (traffic) if (FramePlAnim.Frame > 0) FramePlAnim.Step = -100;  else FramePlAnim.Step = 0;
    else {
        if (FramePlAnim.Frame == 800) FramePlAnim.Step = 0;
        if (FramePlAnim.Frame <= 700) FramePlAnim.Step = 100;
    }
}

void Correct(Fuul& jerrican, int i, Meteors* meteors, int Nmeteor)
{
    for (int i1 = 0; i1 < Nmeteor; i1++)
    {
        if (i1 != i) {
            if (meteors[i1].collision(meteors[i].getMeteorBounds()))
            {
                meteors[i].restart();  Correct(jerrican, i, meteors, Nmeteor); break;
            }
        }

    }
    if (jerrican.collision(meteors[i].getMeteorBounds())) { meteors[i].restart(); Correct(jerrican, i, meteors, Nmeteor); }
}
void CorrectFuul(Fuul& jerrican, Meteors* meteors, int Nmeteors)
{
    for (int i1 = 0; i1 < Nmeteors; i1++)
    {
        if (meteors[i1].collision(jerrican.getMeteorBounds()))
        {
            jerrican.restart(); CorrectFuul(jerrican, meteors, Nmeteors); break;
        }
    }
}
//int to str
string IntToStr(int number)
{
    ostringstream TextString;  
    TextString << number;		
    return TextString.str();
}