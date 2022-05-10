#include "Entity.h"

HBITMAP Entity::BIT_Character = NULL;

int Entity::GetHealth() {

	return Health;
}

void Entity::SetHealth(int newHealth) {
	Health = newHealth;
}

bool Entity::GetDamages(int x)
{
	return false;
}

void Entity::SetType(int x)
{
	this->Type = x;
}

int Entity::GetType()
{
	return this->Type;
}

void Entity::SetCharacterBit(HINSTANCE hInst)
{
	BIT_Character = NULL;
}

void Entity::DeleteCharacterBit()
{
	DeleteObject(BIT_Character);
}
