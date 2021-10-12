#include "Renderer.h"
#include "Framebuffer.h"
#include <iostream>
#include <SDL.h>

int main(int, char**)
{
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);
	
	std::unique_ptr<Framebuffer> frameBuffer = std::make_unique<Framebuffer>(renderer.get(), renderer->width, renderer->height);

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		frameBuffer->Clear({ 0, 0, 0, 0 });
        for (int i = 0; i < 100; i++)
        {
            frameBuffer->DrawPoint(rand() % frameBuffer->width, rand() % frameBuffer->height, { 0, 255, 0, 0 });
        }
        for (int i = 0; i < 20; i++)
        {
            frameBuffer->DrawRect(rand() % frameBuffer->width, rand() % frameBuffer->height, 20, 20, { 0, 0, 255, 0 });
        }
        for (int i = 0; i < 20; i++)
        {
            frameBuffer->DrawLine(frameBuffer->width >> 1, frameBuffer->height >> 1, rand() % frameBuffer->width, rand() % frameBuffer->height, { 255, 255, 255, 0 });
        }



        for (int i = 0; i < 10; i++)
        {
            frameBuffer->DrawQuadraticCurve(
                rand() % frameBuffer->width, rand() % frameBuffer->height,
                rand() % frameBuffer->width, rand() % frameBuffer->height,
                rand() % frameBuffer->width, rand() % frameBuffer->height, 30, { 255, 255, 0, 255 });
        }
        for (int i = 0; i < 10; i++)
        {
            frameBuffer->DrawCubicCurve(
                rand() % frameBuffer->width, rand() % frameBuffer->height,
                rand() % frameBuffer->width, rand() % frameBuffer->height,
                rand() % frameBuffer->width, rand() % frameBuffer->height,
                rand() % frameBuffer->width, rand() % frameBuffer->height,
                30, { 0, 255, 255, 255 });
        }

		frameBuffer->Update();

		renderer->CopyBuffer(frameBuffer.get());
		renderer->Present();
	}

	SDL_Quit();

	return 0;
}
