#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Source/Engine.h"
#include "Source/Globals.h"
#include "Source/Sound.h"

//// DONT WRITE CODE LIKE THIS (: ////

class Ball {

private:
	sf::CircleShape circle_shape;
	sf::Vector2f pos;
	sf::Color color;

public:
	Ball(float Radius) {
		circle_shape.setRadius(Radius);
	}

	void SetPos(float x, float y) {
		pos = sf::Vector2f(x, y);
	}
	void SetColor(int R, int G, int B, int A = 255) {
		color = sf::Color(R, G, B, A);
	}

	sf::CircleShape GetShape() {
		return circle_shape;
	}

	void Draw(sf::RenderWindow &window){
		circle_shape.setPosition(pos);
		circle_shape.setFillColor(color);
		window.draw(circle_shape);
	}
};


void Movement();
void PaddleBounds();
void input();
void BallBaunce();
int Random_Int(int min, int max);
void RestartGame();
void LaunchBall();

GameObject LeftPaddle(20, 150);
GameObject RightPaddle(20, 150);
Ball pongBall(20);
//Sound LowPitchBlip("pongblipLowPitch.wav");
//Sound HighPitchBlip("pongblipHighPitch.wav");

// paddles
float PaddleSpeed = 400;

float LeftY;
float RightY;
// paddle bounds
float minY = 0, maxY = 350 ;

// ball
float General_Ball_Speed = 460;
float ballY;
float ballX;
float speedY;
float speedX;
float maxBallY, minBallY;


// starting positions
float StartingPosBallX;
float StartingPosBallY;

float StartingPosPaddles;

// general
bool StartFromLeft = false;
bool StartFromRight = false;

void Start() {
	Main_Engine_Window->setTitle("Pong");

	LeftPaddle.SetColor(35, 50, 165);
	RightPaddle.SetColor(160, 35, 50);

	pongBall.SetColor(150, 60, 110);

	// Centering 
	LeftY = (Main_Engine_Window->getSize().y / 2) - (LeftPaddle.GetRectShape().getGlobalBounds().height / 2);
	RightY = (Main_Engine_Window->getSize().y / 2) - (RightPaddle.GetRectShape().getGlobalBounds().height / 2);

	ballY = (Main_Engine_Window->getSize().y / 2) - (pongBall.GetShape().getGlobalBounds().height / 2);
	ballX = (Main_Engine_Window->getSize().x / 2) - (pongBall.GetShape().getGlobalBounds().width / 2);
	
	//ball 
	maxBallY = (Main_Engine_Window->getSize().y) - pongBall.GetShape().getGlobalBounds().height;
	minBallY = 0;
	speedX = General_Ball_Speed;
	speedY = General_Ball_Speed;

	StartingPosBallX = ballX;
	StartingPosBallY = ballY;
	StartingPosPaddles = LeftY;


	LaunchBall();

}



void EventUpdate() {
	input();
}

void LaunchBall() {

	if (Random_Int(1, 4) == 2) {
		StartFromRight = true;
	}
	else {
		StartFromLeft = true;
	}
}

void Update() {

	Main_Engine_Window->clear(sf::Color(20, 1, 21));

	BallBaunce();

	if (StartFromLeft) {
		ballX -= speedX * DeltaTime;
		ballY -= speedY * DeltaTime;
	}
	else if (StartFromRight) {
		ballX += speedX * DeltaTime;
		ballY += speedY * DeltaTime;
	}


	Movement();
	PaddleBounds();

	LeftPaddle.SetPosition(50, LeftY);
	RightPaddle.SetPosition((float)Main_Engine_Window->getSize().x - (float)50 - (20), RightY);

	pongBall.SetPos(ballX, ballY);

	pongBall.Draw(*Main_Engine_Window);
}

void BallBaunce() {
	
	// if colliding with wall
	if (ballY > maxBallY) {
		ballY -= 1;
		speedY *= -1;
	}
	else if (ballY < minBallY) {
		ballY += 1;
		speedY *= -1;
	}

	// if collides with left paddle
	if (pongBall.GetShape().getGlobalBounds().intersects(LeftPaddle.GetRectShape().getGlobalBounds())) {
		ballX += 1;
		speedX *= -1;
	}
	// if collides with right paddle
	else if (pongBall.GetShape().getGlobalBounds().intersects(RightPaddle.GetRectShape().getGlobalBounds())) {
		ballX -= 1;
		speedX *= -1;
	}
}

void RestartGame() {
	ballX = StartingPosBallX;
	ballY = StartingPosBallY;
	LeftY = StartingPosPaddles;
	RightY = StartingPosPaddles;

	speedX = 0;
	speedY = 0;

	StartFromLeft = false;
	StartFromRight = false;

	speedX = General_Ball_Speed;
	speedY = General_Ball_Speed;
	LaunchBall();
}

void PaddleBounds() {
	if (LeftY > maxY) {
		LeftY = maxY;
	}
	else if (LeftY < minY) {
		LeftY = minY;
	}

	if (RightY > maxY) {
		RightY = maxY;
	}
	else if (RightY < minY) {
		RightY = minY;
	}
}

void Movement() {
	if (LeftPaddle.moveUp) {
		LeftY -= PaddleSpeed * DeltaTime;
	}
	else if (LeftPaddle.moveDown == 1) {
		LeftY += PaddleSpeed * DeltaTime;
	}

	if (RightPaddle.moveUp == 1) {
		RightY -= PaddleSpeed * DeltaTime;
	}
	else if (RightPaddle.moveDown == 1) {
		RightY += PaddleSpeed * DeltaTime;
	}

}

void input() {

	if (Input::GetKeyDown(Key::R)) {
		RestartGame();
	}


	if (Input::GetKeyDown(Key::Up)) {
		RightPaddle.moveUp = true;
	}
	else if (Input::GetKeyUp(Key::Up)) {
		RightPaddle.moveUp = false;
	}
	if (Input::GetKeyDown(Key::Down)) {
		RightPaddle.moveDown = true;
	}
	else if (Input::GetKeyUp(Key::Down)) {
		RightPaddle.moveDown = false;
	}

	if (Input::GetKeyDown(Key::W)) {
		LeftPaddle.moveUp = true;
	}
	else if (Input::GetKeyUp(Key::W)) {
		LeftPaddle.moveUp = false;
	}
	if (Input::GetKeyDown(Key::S)) {
		LeftPaddle.moveDown = true;
	}
	else if (Input::GetKeyUp(Key::S)) {
		LeftPaddle.moveDown = false;
	}
}

int Random_Int(int min, int max) {
	int range = max - min + 1;
	int num = rand() % range + min;

	return num;
}