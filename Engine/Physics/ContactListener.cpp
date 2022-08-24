#include "ContactListener.h"
#include "Framework/Actor.h"
#include "Components/CollisionComponent.h"
#include <iostream>

namespace neu
{
	void ContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			Actor* actorA = (Actor*)(fixtureA->GetUserData().pointer);
			Actor* actorB = (Actor*)(fixtureB->GetUserData().pointer);

			//Actor A -> Actor B
			if (actorA->GetComponent<CollisionComponent>())
			{
				actorA->GetComponent<CollisionComponent>()->OnCollisionEnter(actorB);
			}
			// Actor B -> ActorA
			if (actorB->GetComponent<CollisionComponent>())
			{
				actorB->GetComponent<CollisionComponent>()->OnCollisionEnter(actorA);
			}
		}

	}

	void ContactListener::EndContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			Actor* actorA = (Actor*)(fixtureA->GetUserData().pointer);
			Actor* actorB = (Actor*)(fixtureB->GetUserData().pointer);

			//Actor A -> Actor B
			if (actorA->GetComponent<CollisionComponent>())
			{
				actorA->GetComponent<CollisionComponent>()->OnCollisionExit(actorB);
			}
			//Actor B -> Actor A
			if (actorB->GetComponent<CollisionComponent>())
			{
				actorB->GetComponent<CollisionComponent>()->OnCollisionExit(actorA);
			}
		}
	}
}
