#include "Collision.h"
#include "Object.h"


namespace Engine
{
	/*
	//Collision::Collisions(){}

	//Collision::~Collision()	{}

	GLboolean Collision::CheckCollision(Collision &one, Collision &two) // AABB - AABB collision
	{
		// Collision x-axis?
		bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
			two.Position.x + two.Size.x >= one.Position.x;
		// Collision y-axis?
		bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
			two.Position.y + two.Size.y >= one.Position.y;
		// Collision only if on both axes

		return collisionX && collisionY;
	}




	glm::vec2 Collision::Move(GLfloat dt, GLuint window_width)
	{
		// If not stuck to player board
		if (!this->Stuck)
		{
			// Move the ball
			this->Position += this->Velocity * dt;
			// Check if outside window bounds; if so, reverse velocity and restore at correct position
			if (this->Position.x <= 0.0f)
			{
				this->Velocity.x = -this->Velocity.x;
				this->Position.x = 0.0f;
			}
			else if (this->Position.x + this->Size.x >= window_width)
			{
				this->Velocity.x = -this->Velocity.x;
				this->Position.x = window_width - this->Size.x;
			}
			if (this->Position.y <= 0.0f)
			{
				this->Velocity.y = -this->Velocity.y;
				this->Position.y = 0.0f;
			}

		}
		return this->Position;
	}

	void Collision::DoCollisions()
	{
		for (Collision &box : this->Levels[this->Level].Bricks)
		{
			if (!box.Destroyed)
			{
				if (CheckCollision(*Ball, box))
				{
					if (!box.IsSolid)
						box.Destroyed = GL_TRUE;
				}
			}
		}
	}
	*/
}