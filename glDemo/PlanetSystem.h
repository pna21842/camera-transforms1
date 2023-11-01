#pragma once

#include "core.h"

//
// Model a simple planet system with a single planet in the centre and a single moon orbiting the planet
//


struct PlanetaryBody {

	GLuint	textureID;

	float	orbitDistance;
	float	orbitAngle;

	float	rotationAngle;
	float	scale;

	float	orbitSpeed;
	float	rotationSpeed;

	// Constructors

	PlanetaryBody() {

		textureID = 0;
		orbitDistance = 0.0f;
		orbitAngle = 0.0f;
		rotationAngle = 0.0f;
		scale = 1.0f;
		orbitSpeed = 0.0f;
		rotationSpeed = 0.0f;
	}

	PlanetaryBody(GLuint textureID, float orbitDistance, float orbitAngle, float rotationAngle, float scale, float orbitSpeed, float rotationSpeed) {

		this->textureID = textureID;
		this->orbitDistance = orbitDistance;
		this->orbitAngle = orbitAngle;
		this->rotationAngle = rotationAngle;
		this->scale = scale;
		this->orbitSpeed = orbitSpeed;
		this->rotationSpeed = rotationSpeed;
	}

	void update(float tDelta) {

		orbitAngle += orbitSpeed * tDelta;
		rotationAngle += rotationSpeed * tDelta;
	}

	
};


class SimplePlanetSystem {

	// Array of planet textures
	GLuint						planetTexture[11];

	// Array of orbiting planetary bodies
	std::vector<PlanetaryBody>	satelliteSystem;

public:

	// Constructor
	SimplePlanetSystem();
	
	// Initialisation, update (called per-frame) and render functions
	void initialise();
	void update(float tDelta);
	void render(glm::mat4 cameraTransform);
};
