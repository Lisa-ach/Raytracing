#include "Sdl.h"


Sdl::Sdl(int width, int height, const std::string &filename) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erreur d'initialisation de la SDL : " << SDL_GetError() << std::endl ;
        return ;
    }

    window_ = SDL_CreateWindow(filename.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN) ;
    if (!window_) {
        std::cerr << "Erreur lors de la création de la fenêtre SDL : " << SDL_GetError() << std::endl ;
        return ;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED) ;
    if (!renderer_) {
        std::cerr << "Erreur lors de la création du rendu SDL : " << SDL_GetError() << std::endl ;
        return ;
    }
}

Sdl::~Sdl() {
    // On détruit le rendu
    if (renderer_) {
        SDL_DestroyRenderer(renderer_) ;
    }
    // On détruit la fenêtre
    if (window_) {
        SDL_DestroyWindow(window_) ;
    }
    SDL_Quit() ;
}

bool Sdl::isValid() const {
    return window_ != nullptr && renderer_ != nullptr ;
}