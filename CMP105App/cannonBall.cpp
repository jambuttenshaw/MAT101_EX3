#include "cannonBall.h"



cannonBall::cannonBall() :
	cGravity(0, 9.8), //note the axis in the 2D game are positive down and positive right so 9.8 in y is down
	cResitanceForceMagnitude(0.0f),
	pWindow(nullptr), 
	alive(false)
{
	setRadius(10);
	setOrigin(getRadius() / 2.0f, getRadius() / 2.0f);
	setRotation(0);
	setPosition(300, 300);
	setFillColor(sf::Color::Black);
	
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
	//but since we are using vectors we are looking at the horizontal and vertial components of our right triangle (where Vtotal is the hypotonous 
	//if in terms of vectors just keep coding like we have been where a = 0 in x and a = 9.8 in y  (contained in cGravity constant)  our equation is easy with vectors
	sf::Vector2f pos = stepVelocity * dt + 0.5f*cGravity*dt*dt; //ut + 1/2at^2
	stepVelocity += cGravity * dt; // v = u + at
	setPosition(getPosition() + pos);


	////alternatively use t instead of dt, where t is time since launch aka age
	//float t = age;
	//sf::Vector2f pos = InitialVelocity * t + 0.5f*cGravity*t*t;
	//setPosition(startingPosition + pos);


	CheckAgeAndOffScreen();

}

void cannonBall::Draw()
{
	if (!alive)
	{
		return;
	}

	pWindow->draw(*this);

}

void cannonBall::TurnOn(float VelocityMagnitude, float angleRad, sf::Vector2f startingpos)
{
	alive = true;
	age = 0;
	startingPosition = startingpos - sf::Vector2f(getRadius()*0.5f, getRadius()*0.5f);
	InitVelocityMag = VelocityMagnitude; 
	angleRadians = angleRad;
	InitialVelocity = { VelocityMagnitude*cos(angleRadians), VelocityMagnitude*sin(angleRadians) };
	stepVelocity = InitialVelocity;
	setPosition(startingPosition);
}

void cannonBall::TurnOff()
{
	alive = false;
	age = 999999.9f;
}

void cannonBall::CheckAgeAndOffScreen()
{

	if (age > 20.0f)
	{
		alive = false;
		age = 0;
	}
	if (pWindow == nullptr)
	{
		return;
	}
	if (getPosition().x - getRadius() > pWindow->getSize().x ||
		getPosition().y - getRadius() > pWindow->getSize().y ||
		getPosition().x + getRadius() < 0 ||
		getPosition().y + getRadius() < 0 
		)
	{
		alive = false;
		age = 0;
	}
}
