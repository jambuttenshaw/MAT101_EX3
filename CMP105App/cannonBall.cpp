#include "cannonBall.h"



cannonBall::cannonBall() :
	cGravity(0, 9.8), //note the axis in the 2D game are positive down and positive right so 9.8 in y is down
	cResitanceForceMagnitude(0.0f),
	pWindow(nullptr), 
	alive(false)
{

}


cannonBall::~cannonBall()
{
}
 

void cannonBall::update(float dt)
{
	if (!alive)
	{
		return;
	}
	age += dt;
	//Vx = Vcos(angle);  //is a constant velocity b/c no forces acting along the x
	//Vy = Vsin(angle) + 1/2(cGravity.y)
}

void cannonBall::Draw()
{
	if (!alive)
	{
		return;
	}

}

void cannonBall::TurnOn(float VelocityMagnitude, float angleRad, sf::Vector2f startingpos)
{
	alive = true;
	age = 0;
	
	InitVelocityMag = VelocityMagnitude; 
	angleRadians = angleRad;
	InitialVelocity = { VelocityMagnitude*sin(angleRadians), VelocityMagnitude*cos(angleRadians) };
	setPosition(startingpos);
}

void cannonBall::TurnOff()
{
	alive = false;
	age = 999999.9f;
}