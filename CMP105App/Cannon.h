#pragma once
#include "MySprite.h"
#include "Line.h"
#include "cannonBall.h"


class Cannon : public MySprite
{
public:
	Cannon();
	~Cannon();

	void update(float dt);  //this gets called by the game once a frame to keep updating and changing the sprite
	
	void setRenderWindow(sf::RenderWindow* w);
	void setText(sf::Text* t) { pText = t; }
	sf::Vector2f GetUnitVectorFromAngle() const {
		return {  cos(angle), sin(angle) };
	}
	void Draw();
protected:
	void handleInput(float dt);
	void updateCannonBalls(float dt);
	void Launch();
	void drawCannonBalls();
	void drawPrediction();
	sf::Vector2f  GetPreditionLocation(float t);
	cannonBall & GetNextAvailableBall();
	//here we are separating out speed and direction aka velocity


	const sf::Vector2f cGravity;
	float angle; //THIS IS IN RADIANS
	float VelocityMagnitude;

	float dollySpeed;
	float velocityIncrementer;
	//flag to see if the sprite is currently moving
	bool moving;
	bool drag;

	sf::RenderWindow* pWindow;

	sf::Text* pText;

	


	//Example showing how to build a sprite out of base shapes if not using a texture
	RectangleShape baseShape;
	sf::CircleShape hingeShape;
	RectangleShape  barrelShape;

	static const int MAX_CANNON_BALLS = 20;
	cannonBall cannonBalls[MAX_CANNON_BALLS];
	Line line;

	float angularSpeed; //Rate that the cannon can change it's angle



};

