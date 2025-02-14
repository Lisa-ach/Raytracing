#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>
#include "Vector3f.h"
#include <iostream>

/**
 * @brief La classe Sdl permet d'avoir des raccourcis dans le code quand on utilise 
 * la SDL
 * 
 * ATTENTION : des fuites mémoires viennent de la bibliothèque SDL directement
*/

class Sdl {

    private:
        /**
         * @brief La fenêtre dans laquelle on va afficher la scène
        */
        SDL_Window* window_;
        /**
         * @brief Le renderer dans lequel on va dessiner la scène
        */
        SDL_Renderer* renderer_;

    public:

        /**
         * @brief Constructeur paramétré
         * 
         * Crée une instance de la classe Sdl à partir des paramètres donnés
         * 
         * @param width : la largeur voulue de la fenêtre
         * @param height : la hauteur voulue de la fenêtre
         * @param filename : référence vers le nom du fichier dans lequel on veut ouvrir la fenêtre
        */
        Sdl(int width, int height, const std::string &filename) ;

        /**
         * @brief Le desctructeur de la classe Sdl
        */
        ~Sdl() ;

        /**
         * @brief Getter de l'attribut window_
         * 
         * @return L'attribut window_ de la classe
        */
        SDL_Window * getWindow() const {
            return window_ ;
        };
        /**
         * @brief Getter de l'attribut window_
         * 
         * @return L'attribut renderer_ de la classe
        */
        SDL_Renderer* getRenderer() const {
            return renderer_ ;
        };

        /**
         * @brief On vérifie la validité de la fenêtre et du rendu
         * 
         * @return true si les attributs sont bien instanciés, false sinon
        */
        bool isValid() const ;
};

#endif


