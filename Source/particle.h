/*
 * particle.h
 *
 *  Created on: 20 Dec 2019
 *      Author: Samuel Chinedu
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace simulation
{

struct Particle
{
	double m_x;
	double m_y;
private:
	double m_speed;
	double m_direction;
public:
	Particle();
	virtual ~Particle();
	void update(int interval);
private:
	void init();
};

} /* namespace simulation */

#endif /* PARTICLE_H_ */
