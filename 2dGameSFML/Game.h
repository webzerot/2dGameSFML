#pragma once
#include <iostream>
#include <SFML/Audio.hpp>

#include "Source/Engine.h"
#include "Source/Globals.h"
#include "Source/Sound.h"

//// DONT WRITE CODE LIKE THIS (: ////

// Gameplay // 
int maxScore = 4;

std::string LeftWonQuote = "Left Won";
std::string RightWonQuote = "Right Won";

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
void RestartGame(bool Launch);
void CheckPoint();
void LaunchBall();
void UpdateUiScore();
void CheckForWinner();
void InputAfterWin();
void RestartAllGame();

GameObject LeftPaddle(20, 150);
GameObject RightPaddle(20, 150);
Ball pongBall(20);

Text LeftScoreText("0");
Text RightScoreText("0");
Text WinningText("Red Won");
Text PressSpaceToStart("Press The Spacebar");

int LeftScore = 0;
int RightScore = 0;

// sound
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

bool LeftWon = false;
bool RightWon = false;

bool ActiveInput = true;

bool FirstRound = true;

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

	// Text

	LeftScoreText.SetColor(255, 255, 255);
	RightScoreText.SetColor(255, 255, 255);
	LeftScoreText.setPosition(200, 10);
	RightScoreText.setPosition(500, 10);
	RightScoreText.fontSize = 50;
	LeftScoreText.fontSize = 50;

	WinningText.fontSize = 80;
	WinningText.SetColor(255, 255, 255);
	WinningText.setPosition(200, 200);

	PressSpaceToStart.fontSize = 40;
	PressSpaceToStart.SetColor(255, 255, 255);
	PressSpaceToStart.setPosition(200, 400);
	PressSpaceToStart.AutomaticDrawing = true;

	// Disable stuff
	WinningText.AutomaticDrawing = false;

}



void EventUpdate() {
	if (ActiveInput)
		input();
	if (LeftWon || RightWon) {
		InputAfterWin();
	}
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
	CheckPoint();
	UpdateUiScore();
	CheckForWinner();

	LeftPaddle.SetPosition(50, LeftY);
	RightPaddle.SetPosition((float)Main_Engine_Window->getSize().x - (float)50 - (20), RightY);

	pongBall.SetPos(ballX, ballY);

	std::cout << "[+] LeftScore : " << LeftScore << " | RightScore : " << RightScore << std::endl;

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

void RestartGame(bool Launch) {
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
	if (Launch)
		LaunchBall();
}

void RestartAllGame() {
	ActiveInput = true;
	WinningText.AutomaticDrawing = false;
	PressSpaceToStart.AutomaticDrawing = true;
	FirstRound = true;

	// reseting positions
	ballX = StartingPosBallX;
	ballY = StartingPosBallY;
	LeftY = StartingPosPaddles;
	RightY = StartingPosPaddles;

	// reseting scores
	LeftScore = 0;
	RightScore = 0;

	LeftWon = false;
	RightWon = false;

	// reseting speed
	speedX = 0;
	speedY = 0;

	// values
	StartFromLeft = false;
	StartFromRight = false;

	speedX = General_Ball_Speed;
	speedY = General_Ball_Speed;

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

void CheckPoint() {
	// checking if a player has scored
	if (ballX < 0) {
		RightScore += 1;
		RestartGame(false);
	}
	else if (ballX > 700) {
		LeftScore += 1;
		RestartGame(false);
	}


	if (RightScore > 0 || LeftScore < 0) {
		FirstRound = false;
	}

	if (RightScore == maxScore) {
		LeftWon = false;
		RightWon = true;
	}

	if (LeftScore == maxScore) {
		RightWon = false;
		LeftWon = true;
	}
}

void CheckForWinner() {
	if (RightWon) {
		WinningText.ChangeText(RightWonQuote);
		WinningText.AutomaticDrawing = true;
	}
	else if (LeftWon) {
		WinningText.ChangeText(LeftWonQuote);
		WinningText.AutomaticDrawing = true;
	}

}

void UpdateUiScore() {
	LeftScoreText.ChangeText(std::to_string(LeftScore));
	RightScoreText.ChangeText(std::to_string(RightScore));
}

void input() {

	if (Input::GetKeyDown(Key::Space)) {
		LaunchBall();
		PressSpaceToStart.AutomaticDrawing = false;
	}

	if (Input::GetKeyDown(Key::R)) {
		RestartGame(true);
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

void InputAfterWin() {
	if (Input::GetKeyDown(Key::Space)) {
		RestartAllGame();
	}
}

int Random_Int(int min, int max) {
	int range = max - min + 1;
	int num = rand() % range + min;

	return num;
}