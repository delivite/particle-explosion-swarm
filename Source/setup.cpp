/*
 * setup.cpp
 *
 *  Created on: 17 Dec 2019
 *      Author: Samuel Chinedu
 */

#include <cstring>
#include <iostream>
#include <cstdlib>

#include "setup.h"

namespace simulation {

Setup::Setup() :
		m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL), m_buffer2(
				NULL) {
}

bool Setup::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Init failed!" << "\n";
		return false;
	}

	m_window = SDL_CreateWindow("My Particle Simulation Exercise",
	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
			SDL_WINDOW_SHOWN);

	if (m_window == NULL) {
		std::cout << "Creating window failed!" << "\n";
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);

	if (m_renderer == NULL) {
		std::cout << "Renderer not created" << "\n";
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	if (m_texture == NULL) {
		std::cout << "Texture not created" << "\n";
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	m_buffer = new Uint32[WIDTH * HEIGHT];
	m_buffer2 = new Uint32[WIDTH * HEIGHT];

	memset(m_buffer, 0, WIDTH * HEIGHT * sizeof(Uint32));
	memset(m_buffer2, 0, WIDTH * HEIGHT * sizeof(Uint32));

	return true;
}

void Setup::boxBlur() {
	Uint32 *temp = m_buffer;
	m_buffer = m_buffer2;
	m_buffer2 = temp;

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			for (int row = -1; row <= 1; row++) {
				for (int col = -1; col <= 1; col++) {
					int currentX = x + col;
					int currentY = y + row;

					if (currentX >= 0 && currentX < WIDTH && currentY >= 0
							&& currentY < HEIGHT) {
						Uint32 color = m_buffer2[currentY * WIDTH + currentX];

						Uint8 red = color >> 24;
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			}
			Uint8 red = redTotal / 9;
			Uint8 green = greenTotal / 9;
			Uint8 blue = blueTotal / 9;

			setPixel(x, y, red, green, blue);
		}
	}
}

void Setup::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
		return;
	}
	Uint32 color = 0;

	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xFF;

	m_buffer[(y * WIDTH) + x] = color;
}

void Setup::update() {
	SDL_UpdateTexture(m_texture, NULL, m_buffer, WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

bool Setup::processEvents() {

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
}

void Setup::close() {
	delete[] m_buffer;
	delete[] m_buffer2;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

}
/* namespace simulation */
