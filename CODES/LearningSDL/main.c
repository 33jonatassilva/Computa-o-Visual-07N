#include <stdio.h>
#include <SDL3/SDL.h>
//#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>


typedef struct Window Window;
struct Window
{
	SDL_Window *window;
	SDL_Renderer *renderer;
};

typedef struct Image Image;
struct Image
{
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_FRect rect;
};


static Window p_window = 
{ 
	.window = NULL,
	.renderer = NULL,
};
	
	
static Image image = 
{
	.surface = NULL,
	.texture = NULL,
	.rect = {0.0f},
};


int main()
{
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Erro ao iniciar a SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }


    SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	
	


	if(!SDL_CreateWindowAndRenderer("JANELA", 400, 400, 0, &window, &renderer))
	{
		SDL_Log("Erro ao criar a janela e/ou renderizador: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	
	
	SDL_Texture *texPng = IMG_LoadTexture(renderer, "teste.jpg");
	if(!texPng)
	{
		SDL_Log("Erro ao carregar imagem '%s': %s", "teste.jpg", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	
	SDL_FRect pngRect =
	{
		.x = 0.0f,
		.y = 0.0f,
	};
	SDL_GetTextureSize(texPng, &pngRect.w, &pngRect.h);

	SDL_SetWindowSize(window, pngRect.w, pngRect.h);
	
	SDL_Event event;
	
	bool isRunning = true;
	
	while(isRunning)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_EVENT_QUIT:
					isRunning = false;
					break;
				case SDL_EVENT_MOUSE_MOTION:
					//SDL_SetWindowTitle(window, "JANELA");
			}
		}
		
		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
		SDL_RenderClear(renderer);
		
		SDL_RenderTexture(renderer, texPng, NULL, &pngRect);
		
		SDL_RenderPresent(renderer);
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	
	return 0;

}
