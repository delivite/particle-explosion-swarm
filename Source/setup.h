/*
 * setup.h
 *
 *  Created on: 17 Dec 2019
 *      Author: Samuel Chinedu
 */

#ifndef SETUP_H_
#define SETUP_H_

#include <SDL.h>


namespace simulation
{
// Namespace Simulation

class Setup
{

public:
	const static int WIDTH = 800;
	const static int HEIGHT = 600;

private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_buffer;
	Uint32 *m_buffer2;

public:
	Setup();
	bool init();
	bool processEvents();
	void close();
	void update();
	void boxBlur();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);


};

} /* namespace simulation */

#endif /* SETUP_H_ */
