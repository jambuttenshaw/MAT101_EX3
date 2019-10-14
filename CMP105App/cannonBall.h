#pragma once
#include "MySprite.h"



class cannonBall: public sf::CircleShape
{
public:
	cannonBall();
	~cannonBall();
	void setRenderWindow(sf::RenderWindow* w) {
		pWindow = w;
	}
	void update(float dt);  //this gets called by the game once a frame to keep updating and changing the sprite
	void Draw();
	void TurnOn(float VelocityMagnitude, float angleRad, sf::Vector2f startingpos);
	bool IsAlive() const { return alive; }
	float GetAge() const { return age; }
protected:
	void TurnOff();
	void CheckAgeAndOffScreen();
	
	



	sf::Vector2f InitialVelocity;
	sf::Vector2f stepVelocity;
	sf::Vector2f startingPosition;
	float InitVelocityMag;  // The magnitude of the inital velocity the V in our word problems
	float angleRadians;  //the angle of launch, can be calculated from the vector Inital Velocity

	//here we are separating out speed and direction aka velocity
	float speed;
	sf::Vector2f direction;

	const sf::Vector2f cGravity;
	const float cResitanceForceMagnitude;
	float mass;

	sf::RenderWindow* pWindow;
	
	//flag to see if the sprite is currently in use 
	bool alive;
	float age;
};


