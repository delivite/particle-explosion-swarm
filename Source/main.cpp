//============================================================================
// Name        : main.cpp
// Author      : Samuel Chinedu
// Version     :
// Copyright   : Your copyright notice
// Description : Particle Explosion Simulator using C++ and SDL2
//============================================================================

#include <SDL.h>
#include <time.h>

#include <cmath>
#include <iostream>
#include <cstdlib>

#include "setup.h"
#include "swarm.h"

using namespace simulation;

int main(int argc, char **argv)
{
	srand(time(NULL));

	Setup setup;

	if (setup.init() == false)
	{
		std::cout << "Error" << "\n";
	}

	Swarm swarm;
	auto wide = Setup::WIDTH / 2;
	auto high = Setup::HEIGHT/2;
	while (true)
	{
		int elapsed = SDL_GetTicks();

		swarm.update(elapsed);

		unsigned char red = (unsigned char) ((1 + sin(elapsed * 0.0001)) * 128);
		unsigned char green = (unsigned char) ((1
				+ sin(elapsed * 0.0002)) * 128);
		unsigned char blue =
				(unsigned char) ((1 + sin(elapsed * 0.0003)) * 128);

		const Particle *const pParticles = swarm.getParticles();

		for (int i = 0; i < Swarm::NPARTICLES; i++)
		{
			Particle particle = pParticles[i];

			int x = (particle.m_x + 1) * wide;
			int y = particle.m_y * wide + high;

			setup.setPixel(x, y, red, green, blue);
		}
		setup.boxBlur();
		setup.update();

		if (setup.processEvents() == false)
		{
			break;
		}

	}

	setup.close();

	return 0;
}
