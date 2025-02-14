#ifndef SCENE_H
#define SCENE_H

#include "Ray3f.h"
#include "Camera.h"
#include "Sphere.h"
#include "Quad.h"
#include "Material.h"
#include <cmath>
#include <ostream>
#include <string>
#include <vector>

/**
 * @brief La classe qui crée la scène qui sera ensuite affichée dans une fenêtre
 * 
 * Elle permet de mettre en scène tout les éléments de la scène, ainsi que de calculer la luminosité, les ombres, ...
*/
class Scene {
    private :
        /**
         * @brief La caméra qui observe la scène
         * @see Camera
        */
        Camera camera_ ;
        /**
         * @brief L'ensemble des shape présents sur la scène
         * 
         * L'ensemble des shapes correspond au vecteur contenant les pointeurs vers les shapes de la scène
         * 
         * @see Shape
        */
        std::vector<Shape*> shapes_ ;
        /**
         * @brief La source de lumière qui éclaire la scène 
         * @see Ray3f
        */
        Ray3f source_ ;

    public :
        
        /**
         * @brief Constructeur paramétré
         * 
         * Crée une instance de la classe Scene à partir des paramètres donnés
         * 
         * @param camera : la caméra de la scène
         * @param shapes : l'ensemble des shapes dans la scène
         * @param source : la source de lumière de la scène
         * @see Camera, Shape, Ray3f
        */
        Scene(Camera camera, std::vector<Shape*> shapes, Ray3f source) ;
        /**
         * @brief Constructeur de copie
         * 
         * Crée une instance de Scene en copiant les attributs de la scène donnée un entrée
         * 
         * @param s : une référence vers la scène dont on veut faire la copie
         */
        Scene(const Scene & s) ; 

        /**
         * @brief Getter de l'attribut camera_
         * 
         * @return L'attribut camera_ de la classe
        */
        Camera get_camera() const { return camera_; }
        /**
         * @brief Getter de l'attribut shapes_
         * 
         * @return L'attribut shapes_ de la classe
        */
        std::vector<Shape*> get_shapes() const { return shapes_; }
        /**
         * @brief Getter de l'attribut source_
         * 
         * @return L'attribut source_ de la classe
        */
        Ray3f get_source() const { return source_; }

        /**
         * @brief Setter de l'attribut camera_
         * 
         * @param camera : la caméra que l'on veut donner à la scène
        */
        void set_camera(Camera camera) { camera_ = camera; }
        /**
         * @brief Setter de l'attribut shapes_
         * 
         * @param shapes : l'ensemble des shape que l'on veut donner à la scène
        */
        void set_shapes(std::vector<Shape*> shapes) { shapes_ = shapes; }
        /**
         * @brief Setter de l'attribut source_
         * 
         * @param source : la source de lumière que l'on veut donner à la scène
        */
        void set_source(Ray3f source) { source_ = source; }

        /**
         * @brief L'opérateur = de la classe
         * 
         * @param v : référence vers la scène que l'on veut attribuer
         * 
         * @return Référence vers la scène attribuée
        */
        Scene & operator=(const Scene& s);

        /**
         * @brief Fonction qui permet de savoir, pour un rayon donné, l'intersection avec la sphère LA PLUS PROCHE
         * 
         * Elle est utilisée dans scene.render et instancie les valeurs des paramètres P, N et t si il y a intersection. 
         * Sinon, garde les valeurs en entrée.
         * 
         * @param d : référence vers le rayon dont on veut savoir s'il y a intersection
         * @param P : pointeur vers le point avec lequel il y a une intersection, si elle existe
         * @param N : pointeur vers la normale au point P
         * @param sphere_id : pointeur de l'identifiant dans shapes_ dont on veut savoir s'il y a intersection avec le rayon
         * @param t : pointeur vers la valeur de t au point d'intersection P, s'il existe
         * @see Ray3f, Vector3f
         * 
         * @return true si il y a intersection, false sinon
        */
        bool intersection (const Ray3f & d, Vector3f * P, Vector3f * N, int * sphere_id, float * t) const ;

        /**
         * @brief 
         * 
         * Cette fonction retourne un Material pour le rayon donné. La fonction prend en entrée un rayon donné et un nombre de rebonds de ce rayon.
         * La fonction vérifie s'il y a une intersection, et si oui prend la plus proche, en faisant un appel à la fonction
         * Scene::intersection. Ensuite, s'il y a intersection, elle regarde si l'objet intersecté est un miroir, si oui,
         * elle fait un appel récursif. Sinon, elle applique l'éclairage direct (+ éclairage indirect mais ce dernier commenté)
         * afin d'obtenir les composantes de couleur du Material.
         * 
         * @param ray : référence
         * @param nb_rebonds : 
         * @see Ray3f
         * 
         * @return 
         * @see Material
        */
        Material get_color(const Ray3f & ray, int nb_rebonds) const ;

        /**
         * @brief Crée la fenêtre qui s'ouvre pour afficher la scène et enregistre aussi la scène au format BNG.
         * 
         * @param width : la largeur voulue de la fenêtre
         * @param height : la hauteur voulue de la fenêtre
         * @param filename : référence vers le nom du fichier de la fenêtre
        */
        void render(int width, int height, const std::string & filename);
};

/**
 * @brief L'opérateur << pour afficher les informations de la scène
 * 
 * Affiche les informations de la scène donnée sous le format suivant : 
 * Camera : camera_
 * Source : source_
 * Shapes : 
 * 
 * @param st : le flux sur lequel on veut afficher la scène
 * @param s : référence de la scène dont on veut afficher les informations
 * 
 * @return la référence vers le flux modifié
*/
std::ostream& operator<<(std::ostream & st, const Scene & s);

#endif
