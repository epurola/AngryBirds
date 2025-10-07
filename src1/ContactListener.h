#include <box2d/box2d.h>
#include "Enemy.h"

class ContactListener : public b2ContactListener {
public:
	float treshold = 5.8f;

	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override {

		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB = contact->GetFixtureB()->GetBody();

		float maxImpulse = 0.f;

		for (int i = 0; i < impulse->count; i++) {
			maxImpulse = std::max(maxImpulse, impulse->normalImpulses[i]);
		}

		if (maxImpulse > treshold) {
			Enemy* enemyA = reinterpret_cast<Enemy*>(bodyA->GetUserData().pointer);
			Enemy* enemyB = reinterpret_cast<Enemy*>(bodyB->GetUserData().pointer);

			if (enemyA) enemyA->kill();
			if (enemyB) enemyB->kill();
		}
	}
};