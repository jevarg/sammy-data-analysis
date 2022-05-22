#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s audio_file\n", argv[0]);
        return 1;
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return 2;
    }

    SDL_Window *window = SDL_CreateWindow("Audio test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 200, 0);
    if (window == NULL)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        return 2;
    }

    if (Mix_OpenAudio(11025, AUDIO_S8, 1, 8) == -1)
    {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        return 2;
    }

    size_t size = 0;
    void *sndData = SDL_LoadFile(argv[1], &size);
    if (sndData == NULL)
    {
        printf("SDL_LoadFile: %s\n", SDL_GetError());
        return 2;
    }

    
    
    Mix_Chunk *chunk = Mix_QuickLoad_RAW(sndData, size);
    if (chunk == NULL)
    {
        printf("Mix_QuickLoad_RAW: %s\n", Mix_GetError());
        return 2;
    }

    Mix_PlayChannel(1, chunk, 0);

    SDL_Event event;
    bool keepGoing = true;
    while (keepGoing)
    {
        SDL_PollEvent(&event);
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            keepGoing = false;
            break;

        default:
            break;
        }

        SDL_Delay(1000/60);
    }

    // Destroy window
    SDL_DestroyWindow(window);
    SDL_free(sndData);
    Mix_CloseAudio();
    return 0;
}
