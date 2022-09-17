#pragma once

#include "Vector2D.h"

#define MASSA 0.8f
#define GRAVITY 9.8f

#define FORWARD -1
#define BACKWARD 1

#define UPWARD -1
#define DOWNWARD 1

class RigidBody2D
{
public:
    RigidBody2D()
    {
        _mass = MASSA;
        _gravity = GRAVITY;
    }

    inline void SetMass(float mass) { _mass = mass; }
    inline void SetGravity(float gravity) { _gravity = gravity; }

    inline void ApplyForce(Vector2D force) { _force = force; }
    inline void ApplyForceX(float x) { _force.X = x; }
    inline void ApplyForceY(float y) { _force.Y = y; }
    inline void UnSetForce() { _force = Vector2D(0, 0); }

    inline void ApplyFriction(Vector2D friction) { _friction = friction; }
    inline void ApplyFrictionX(float x) { _friction.X = x; }
    inline void ApplyFrictionY(float y) { _friction.Y = y; }
    inline void UnSetFriction() { _friction = Vector2D(0, 0); }

    inline float GetMass() { return _mass; }
    inline Vector2D GetPosition() { return _position; }
    inline Vector2D GetVelocity() { return _velocity; }
    inline Vector2D GetAccelaration() { return _accelaration; }

    void Update(float dt)
    {
        _accelaration.X = (_force.X + _friction.X) / _mass;
        _accelaration.Y = _gravity + _force.Y/_mass;
        _velocity = _accelaration;
        _position.X = _velocity.X;
        _position.Y = _velocity.Y; 
    }
private:
    float _mass, _gravity;
    Vector2D _force, _friction, _position, _velocity, _accelaration;

};