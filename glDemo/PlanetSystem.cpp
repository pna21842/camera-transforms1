
#include "PlanetSystem.h"
#include "TextureLoader.h"
#include "TextureQuad.h"


using namespace std;
using namespace glm;


// Constructor
SimplePlanetSystem::SimplePlanetSystem() {}


// Initialisation, update (called per-frame) and render functions...

// Initialise planet system with given properties for size and orbit distance / speed.
void SimplePlanetSystem::initialise() {

	// Load textures
	
	// Sun texture from NASA
	planetTexture[0] = loadTexture(string("Assets\\Textures\\sun.png"), FIF_PNG);
	// Planet Textures from Master of Orion II: Battle at Antares (https://www.spriters-resource.com/pc_computer/masteroforioniibattleatantares/sheet/206151/)
	planetTexture[1] = loadTexture(string("Assets\\Textures\\planet01.png"), FIF_PNG);
	planetTexture[2] = loadTexture(string("Assets\\Textures\\planet02.png"), FIF_PNG);
	planetTexture[3] = loadTexture(string("Assets\\Textures\\planet03.png"), FIF_PNG);
	planetTexture[4] = loadTexture(string("Assets\\Textures\\planet04.png"), FIF_PNG);
	planetTexture[5] = loadTexture(string("Assets\\Textures\\planet05.png"), FIF_PNG);
	planetTexture[6] = loadTexture(string("Assets\\Textures\\planet06.png"), FIF_PNG);
	planetTexture[7] = loadTexture(string("Assets\\Textures\\planet07.png"), FIF_PNG);
	planetTexture[8] = loadTexture(string("Assets\\Textures\\planet08.png"), FIF_PNG);
	planetTexture[9] = loadTexture(string("Assets\\Textures\\planet09.png"), FIF_PNG);
	planetTexture[10] = loadTexture(string("Assets\\Textures\\planet10.png"), FIF_PNG);

	// Setup orbiting bodies...
	
	satelliteSystem = vector<PlanetaryBody>(4);

	satelliteSystem[0] = PlanetaryBody(planetTexture[0], 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f);
	satelliteSystem[1] = PlanetaryBody(planetTexture[1], 3.0f, 0.0f, 0.0f, 0.5f, radians(20.0f), radians(10.0f));
	satelliteSystem[2] = PlanetaryBody(planetTexture[2], 7.0f, radians(90.0f), 0.0f, 0.7f, radians(5.0f), radians(90.0f));
	satelliteSystem[3] = PlanetaryBody(planetTexture[6], 11.0f, radians(-45.0f), 0.0f, 1.5f, radians(10.0f), radians(20.0f));
}



// Update is called per-frame in the main update function - we change the orbit and moon rotation values so when we create the matrices at render time they model the new position and orientation of the moon.
void SimplePlanetSystem::update(float tDelta) {

	for (int i = 0; i < satelliteSystem.size(); i++) {
		satelliteSystem[i].update(tDelta);
	}
}


// Render planets
void SimplePlanetSystem::render(mat4 cameraTransform) {

	// Enable Texturing and alpha blending for planet rendering
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	textureQuadPreRender();

	// Transform and render each planet (use currentTransform parameter directly)

	for (int i = 0; i < satelliteSystem.size(); i++) {

		glBindTexture(GL_TEXTURE_2D, satelliteSystem[i].textureID);

		mat4 scale = glm::scale(identity<mat4>(), vec3(satelliteSystem[i].scale, satelliteSystem[i].scale, 1.0f));
		mat4 rotation = rotate(identity<mat4>(), satelliteSystem[i].rotationAngle, vec3(0.0f, 0.0f, 1.0f));
		mat4 translate = glm::translate(identity<mat4>(), vec3(satelliteSystem[i].orbitDistance, 0.0f, 0.0f));
		mat4 orbitRotation = rotate(identity<mat4>(), satelliteSystem[i].orbitAngle, vec3(0.0f, 0.0f, 1.0f));

		mat4 T = cameraTransform * orbitRotation * translate * rotation * scale;
		glLoadMatrixf((GLfloat*)&T);

		textureQuadRender();
	}

	textureQuadPostRender();

	// Disable texturing and alpha blending
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}