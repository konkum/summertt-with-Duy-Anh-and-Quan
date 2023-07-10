#pragma once

class Health {
protected:
	float maxHealth = 100.0f;
	float currentHealth = 100.0f;
public:
	Health() {
		currentHealth = maxHealth;
	}
	virtual void TakeDamage(float damage) = 0;
	virtual void Die() = 0;
};