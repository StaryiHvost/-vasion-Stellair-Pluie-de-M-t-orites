#pragma once
#include <SFML/Graphics.hpp>
#include"Meteors.h"
#include "Fuul.h"
#include<string>
#include<sstream>

using namespace sf;
using namespace std;

struct FrameAnim
    {
    int Frame = 0;
    int Step = 100;
    int Frame1 = 0;
    int Step1 = 100;
    };
//mov navire
void playermove(Sprite& player, Vector2f& moveRec);
//animation de navir
void playeranim(Sprite& player, FrameAnim& FramePlAnim, int traffic);
//verification de la coincidence des coordonnees des meteorites
void Correct(Fuul& jerrican, int i, Meteors* meteors, int Nmeteor);
//verification de la coincidence des coordonnees du jerrican avec fuel
void CorrectFuul(Fuul& jerrican, Meteors* meteors, int Nmeteor);

string IntToStr(int number);