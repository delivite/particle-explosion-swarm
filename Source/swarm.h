/*
 * swarm.h
 *
 *  Created on: 20 Dec 2019
 *      Author: Samuel Chinedu
 */

#ifndef SWARM_H_
#define SWARM_H_

#include "particle.h"
namespace simulation
{

class Swarm
{
public:
	const static int NPARTICLES = 8000;
private:
	Particle *m_pParticles;
	int lastTime;
public:
	Swarm();
	virtual ~Swarm();
	const Particle * const getParticles(){return m_pParticles;};
	void update(int elapsed);
};

} /* namespace simulation */

#endif /* SWARM_H_ */
