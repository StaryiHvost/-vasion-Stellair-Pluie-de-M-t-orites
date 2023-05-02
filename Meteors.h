#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class Meteors
{
public:
	Meteors();							//constructeur
	~Meteors();							//destr

	void move(float& time);              //mouvement de meteorite
	void draw(RenderWindow& window);     //dessin de meteorite
	void animation();					 //animation de meteorite
	bool collision(FloatRect object);    //impact de meteorite

	virtual void restart();				 //new coord
	const FloatRect getMeteorBounds();  //position en coordonnés globale
	bool newborn;

	Vector2f getPosBonus()
	{
		return PosBonus;
	}
protected:
	Sprite SpaceObject;					  //object meteorite
	Texture TextureObject;			      //texture de meteorite
	Vector2f PosBonus;
private:

	int xsp[5]{ 3,73,135,198,262 };       //coord text x
	int ysp[6]{ 3,68,132,200,265,325 };		//coord texture y
	int ix, iy = 0;							//decalage
	int st = 0;								//step
};

