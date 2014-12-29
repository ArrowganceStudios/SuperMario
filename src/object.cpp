#include "object.hpp"

using namespace Mario;

void Object::OnUpdate(float dt)
{
    pos_x += dir_x * dt;
}

void Object::OnDraw()
{
    
}
