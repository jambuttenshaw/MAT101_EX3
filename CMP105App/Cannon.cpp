#include "Cannon.h"

#include "ToString.h"
#define RAD2DEG (180.0/GAME_PI)

Cannon::Cannon():
	pWindow(nullptr),
	VelocityMagnitude(120),
	angle(-GAME_PI/4.0f), 
	cGravity(0, 9.8f), //note the axis in the 2D game are positive down and positive right so 9.8 in y is down
	angularSpeed(GAME_PI/8.0f),
	dollySpeed(100.0f),
	velocityIncrementer(20)
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






	if (pText != nullptr)
	{
		std::string otext = "Velocity = " + ToString(VelocityMagnitude) + ", angle = " + ToString(angle*RAD2DEG*-1);
		pText->setString(otext);
	}
	//Update the subcomponents, only a few so do here if many parameterize and put into a method/function
	hingeShape.setPosition(getPosition());
	barrelShape.setPosition(getPosition());
	barrelShape.setRotation(static_cast<float>(angle*RAD2DEG));
	baseShape.setPosition(getPosition());

	
}

void Cannon::setRenderWindow(sf::RenderWindow * w)
{
	 pWindow = w;
	for (int i = 0; i < MAX_CANNON_BALLS; ++i)
	{
		cannonBalls[i].setRenderWindow(w);
	}
	
}

void Cannon::updateCannonBalls(float dt)
{
	for (int i = 0; i < MAX_CANNON_BALLS; ++i)
	{
		if (cannonBalls[i].IsAlive())
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
		float time_tick = i / 20.0f;
		//set line seg
		line.pts[0].position = GetPreditionLocation(time_tick);
		time_tick = (i + 1.0f) / 20.0f;
		line.pts[1].position = GetPreditionLocation(time_tick);
		//draw line seg
		line.Draw(pWindow);
	}

}
sf::Vector2f Cannon::GetPreditionLocation(float t)
{

	////s = ut + 1/2 at^2
	////here we have yet to update the variable velocity so it is the vel of last frame aka u
	//setPosition(getPosition() + velocity*dt + 0.5f*direction*acceleration*dt*dt);
	//velocity = velocity + (direction * acceleration) * dt; ////we need to update velocity to store the change between frames

	sf::Vector2f pos = GetUnitVectorFromAngle()*VelocityMagnitude*t + 0.5f*cGravity*t*t;
	return getPosition() + pos;
}

cannonBall & Cannon::GetNextAvailableBall()
{
	for (int i = 0; i < MAX_CANNON_BALLS; ++i)
	{
		if (!cannonBalls[i].IsAlive())
		{
			return cannonBalls[i];
		}
	}
	int oldIndex = 0;
	for (int i = 1; i < MAX_CANNON_BALLS; ++i)
	{
		if (cannonBalls[i].GetAge() > cannonBalls[oldIndex].GetAge())
		{
			oldIndex = i;
		}
	}
	return cannonBalls[oldIndex];
}


void Cannon::Draw()
{
	
	
	drawPrediction();
	//draw all active cannonballs
	drawCannonBalls();
	pWindow->draw(barrelShape);
	pWindow->draw(baseShape);
	pWindow->draw(hingeShape);

	
}


void Cannon::handleInput(float dt)
{
	//UP
	if (input->isKeyDown(sf::Keyboard::W))
	{
		move(sf::Vector2f(0,- 1)*dollySpeed*dt);
	}
	//DOWN
	if (input->isKeyDown(sf::Keyboard::S))
	{
		move(sf::Vector2f(0, 1)*dollySpeed*dt);
	}
	//LEFT
	if (input->isKeyDown(sf::Keyboard::A))
	{
		move(sf::Vector2f(-1,0)*dollySpeed*dt);
	}
	//RIGHT
	if (input->isKeyDown(sf::Keyboard::D))
	{
		move(sf::Vector2f(1, 0)*dollySpeed*dt);
	}
	//SPACE for launching a cannon ball
	if (input->isKeyJustDown(sf::Keyboard::Space))
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
	if (input->isKeyDown(sf::Keyboard::Up))
	{
		VelocityMagnitude += velocityIncrementer * dt; 
	}
	if (input->isKeyDown(sf::Keyboard::Down))
	{
		VelocityMagnitude -= velocityIncrementer * dt;
	}

	if (angle > 0)
	{
		angle -= 2 * GAME_PI;
	}
	if (angle <= -2 * GAME_PI)
	{
		angle += 2 * GAME_PI;
	}
	

}

void Cannon::Launch()
{
	//Take the current set up
	//angle, Velocity, position and use that to grab a ball
	cannonBall& nextCannonBall = GetNextAvailableBall();
	nextCannonBall.TurnOn(VelocityMagnitude, angle, getPosition());

	//could do some animation or smoke here fwiw
}


Cannon::~Cannon()
{
}
