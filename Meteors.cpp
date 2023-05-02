#include "Meteors.h"

Meteors::Meteors()            
{
	TextureObject.loadFromFile("Image/asteroid.png");
	SpaceObject.setTexture(TextureObject);
	SpaceObject.setTextureRect(IntRect(262, 325, 55, 50));
	restart();
}

Meteors::~Meteors()           
{

}
void Meteors::draw(RenderWindow& window)
{
	window.draw(SpaceObject);
}
void Meteors::move(float& time)
{
	newborn = false;
	SpaceObject.move(static_cast<float>(-0.5 * time), 0);
	PosBonus = SpaceObject.getPosition();
	if (SpaceObject.getPosition().x < -60) restart();
}
void Meteors::animation()
{
	if (st > 0) {
		SpaceObject.setTextureRect(IntRect(xsp[ix], ysp[iy], 50, 45));
		ix += st;
		if (ix > 4) { ix = 0; iy++; if (iy > 5) iy = 0; }
	}
}
bool Meteors::collision(FloatRect object)
{
	if (SpaceObject.getGlobalBounds().intersects(object)) return true;

	return false;
}
void Meteors::restart()
{
	newborn = true;
	float s = static_cast<float>(rand() % 20 + 10);		//echelle de meteorite aleatoire
	float x = static_cast<float>(rand() % 1280 + 1280);			//position aleatoire d'une meteorite dans l'espace
	float y = static_cast<float>(rand() % 540 + 130);			//position aleatoire d'une meteorite dans l'espace
	SpaceObject.setPosition(Vector2f(x, y));
	SpaceObject.setScale(s / 20, s / 20);
	ix = rand() % 4;                                    
	iy = rand() % 5;                                     
	st = rand() % 2;

	PosBonus = SpaceObject.getPosition();
}

const FloatRect Meteors::getMeteorBounds()
{
	return SpaceObject.getGlobalBounds();
}