#pragma once

// Movement physics is based on this information:
// https://web.archive.org/web/20130807122227/http://i276.photobucket.com/albums/kk21/jdaster64/smb_playerphysics.png

#include "../../Settings/MovementComponentSettings.h"

class Character;
class AudioClip;

struct MovementInput
{
	bool left;
	bool right;
	bool run;
	bool jump;
	bool duck;

	MovementInput(bool left = false, bool right = false, bool run = false, bool jump = false, bool duck = false)
		:
		left(left),
		right(right),
		run(run),
		jump(jump),
		duck(duck)
	{}
};

enum class MovementState
{
	Standing = 0,
	Running = 1,
	TurningAround = 2,
	Jumping = 3,
	Ducking = 4,
};

class MovementComponent
{
public:
	MovementComponent(Character* character, MovementComponentSettings settings);
	~MovementComponent();

	void Update(MovementInput input, const float deltaTime);
	void ForceJump();
	MovementState GetState();
	int GetMovementDirection();
	bool IsGrounded();

private:
	void MoveHorizontal(const bool leftInput, const bool rightInput, const bool runInput, const bool duckInput, const float deltaTime);
	void MoveVertical(const bool jumpInput, const bool duckInput, const float deltaTime);
	bool ShouldRun(const bool runInput, const float deltaTime);
	float GetTurnaroundSpeed();

private:
	Character* character;
	AudioClip* jumpClip;

	MovementState state;
	bool isGrounded;
	int movementDirection;

	float runningSpeed;
	float walkingAcceleration;
	float runningAcceleration;
	float releaseDeceleration;
	float skiddingDeceleration;
	float skidTurnaroundSpeed;
	float runningDecelerationDelay;
	float runningDecelerationTimer;

	float airWalkingTurnaroundSpeed;
	float airRunningTurnaroundSpeed;

	float minJumpSpeed;
	float maxJumpSpeed;
	float maxJumpTime;
	float jumpDecelaration;
	float jumpTimer;
	bool isJumping;
	bool forceJump;

	bool jumpClipPlayed;
};

