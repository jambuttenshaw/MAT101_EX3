#pragma once
#include "MySprite.h"



class cannonBall: public MySprite
{
public:
	cannonBall();
	~cannonBall();

	void update(float dt);  //this gets called by the game once a frame to keep updating and changing the sprite
	void Draw();
	void TurnOn(float VelocityMagnitude, float angleRad, sf::Vector2f startingpos);
	bool IsAlive() const { return alive; }
protected:
	void TurnOff();
	
	



	sf::Vector2f InitialVelocity;
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


