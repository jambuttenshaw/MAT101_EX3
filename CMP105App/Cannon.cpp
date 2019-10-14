#include "Cannon.h"

#define RAD2DEG (180.0/GAME_PI)

Cannon::Cannon():
	pWindow(nullptr),
	VelocityMagnitude(30),
	angle(-GAME_PI/4.0f), 
	cGravity(0, 9.8f), //note the axis in the 2D game are positive down and positive right so 9.8 in y is down
	angularSpeed(GAME_PI/8.0f)
{

	line.pts[0].color = sf::Color::Yellow;
	line.pts[0].position = sf::Vector2f(0, 0);
	line.pts[1].color = sf::Color::Yellow;
	line.pts[1].position = sf::Vector2f(0, 0);


	hingeShape.setRadius(12.5f);
	hingeShape.setOrigin(hingeShape.getRadius(), hingeShape.getRadius());
	hingeShape.setRotation(90);
	hingeShape.setPosition(getPosition());
	hingeShape.setFillColor(sf::Color::Blue);


	barrelShape.setSize(sf::Vector2f(50, 25));
	barrelShape.setOrigin(0, barrelShape.getSize().y*0.5f);
	barrelShape.setRotation(static_cast<float>(angle*RAD2DEG));
	barrelShape.setPosition(getPosition());
	barrelShape.setFillColor(sf::Color::Red);



	baseShape.setSize(sf::Vector2f(100, 25));
	baseShape.setOrigin(baseShape.getSize().x*0.5f, -hingeShape.getRadius());
	baseShape.setRotation(0);
	baseShape.setPosition(getPosition());
	baseShape.setFillColor(sf::Color::Green);

}


void Cannon::update(float dt)
{
	handleInput(dt);
	updateCannonBalls(dt);






	//Update the subcomponents, only a few so do here if many parameterize and put into a method/function
	hingeShape.setPosition(getPosition());
	barrelShape.setPosition(getPosition());
	barrelShape.setRotation(static_cast<float>(angle*RAD2DEG));
	baseShape.setPosition(getPosition());
}

void Cannon::updateCannonBalls(float dt)
{
	for (int i = 0; i < MAX_CANNON_BALLS; ++i)
	{
		if (cannonBalls[i].isAlive())
		{
			cannonBalls[i].update(dt);
		}
	}
}

void Cannon::drawCannonBalls()
{
	for (int i = 0; i < MAX_CANNON_BALLS; ++i)
	{
		cannonBalls[i].Draw();
	}
}

void Cannon::drawPrediction()
{
	//do loop
	//choosing to do aprox 5 sec //moving 2 ticks to get dotted effect
	for (int i = 0; i < 60 * 5; i += 2)
	{
		//get position at i and i+1 to get line
		float time_tick = i / 60.0f; //60fps
		//set line seg
		line.pts[0].position = GetPreditionLocation(time_tick);
		time_tick = (i + 1.0f) / 60.0f;
		line.pts[1].position = GetPreditionLocation(time_tick);
		//draw line seg
		line.Draw(pWindow);
	}

}
sf::Vector2f Cannon::GetPreditionLocation(float t)
{

	return getPosition();
}


void Cannon::Draw()
{
	
	pWindow->draw(barrelShape);
	pWindow->draw(baseShape);
	pWindow->draw(hingeShape);
	//draw all active cannonballs
	drawCannonBalls();
}


void Cannon::handleInput(float dt)
{
	//UP
	if (input->isKeyDown(sf::Keyboard::W))
	{
	}
	//DOWN
	if (input->isKeyDown(sf::Keyboard::S))
	{
	}
	//LEFT
	if (input->isKeyDown(sf::Keyboard::A))
	{
	}
	//RIGHT
	if (input->isKeyDown(sf::Keyboard::D))
	{
	}
	//SPACE for launching a cannon ball
	if (input->isKeyDown(sf::Keyboard::Space))
	{
		Launch();
	}
	if (input->isKeyDown(sf::Keyboard::Right))
	{
		//add to the angle clockwise
		angle += angularSpeed * dt;
	}
	if (input->isKeyDown(sf::Keyboard::Left))
	{
		//subtract to the angle clockwise
		angle -= angularSpeed * dt;
	}

}

void Cannon::Launch()
{
	//Take the current set up
	//angle, Velocity, position and use that to grab a ball
}


Cannon::~Cannon()
{
}
