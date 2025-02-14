#ifndef RAY3F_H
#define RAY3F_H

#include "Vector3f.h"
#include <cmath>
#include <ostream>

/**
 * @brief La classe Ray3f définit les rayons qui vont être utilisés pour calculer la scène
 * 
 * Elle permet de faire les calculs de raytracing dans toutes la scène
*/
class Ray3f {
    private :
        /**
         * @brief L'origine du rayon
         * 
         * L'attribut est appelé centre_ pour ne pas être confondu avec les origin_ des shapes dans la scène
         * 
         * @see Vector3f
        */
        Vector3f centre_ ;
        /**
         * @brief La direction du rayon
         * 
         * L'attribut est appelé centre_ pour ne pas être confondu avec les origin_ des shapes dans la scène
         * 
         * @see Vector3f
        */
        Vector3f direction_ ;
    public :

        /**
         * @brief Constructeur par défaut
         * 
         * Crée une instance de la classe Ray3f avec centre_ et direction_ les vecteurs par défaut de
         * @see Vector3f
        */
        Ray3f() ; 
        /**
         * @brief Constructeur paramétré
         * 
         * Crée une instance de la classe Ray3f à partir des paramètres donnés
         * 
         * @param centre : le centre voulu du rayon 
         * @param direction : la direction voulue du rayon
         * @see Vector3f
        */
        Ray3f(Vector3f centre, Vector3f direction); 

        /**
         * @brief Getter de l'attribut centre_
         * 
         * @return L'attribut centre_ de la classe
        */
        Vector3f get_centre() const {return centre_ ;} ;
        /**
         * @brief Getter de l'attribut direction_
         * 
         * @return L'attribut direction_ de la classe
        */
        Vector3f get_direction() const {return direction_ ;} ;

        /**
         * @brief Setter de l'attribut centre_
         * 
         * @param centre : le centre que l'on veut donner au rayon
        */
        void set_centre(Vector3f centre){ centre_ = centre ;} ;
        /**
         * @brief Setter de l'attribut direction_
         * 
         * @param direction : la direction que l'on veut donner au rayon
        */
        void set_direction(Vector3f direction){ direction_ = direction ;} ;

} ;

/**
 * @brief L'opérateur << pour afficher les informations du rayon
 * 
 * Affiche les informations du rayon donné sous le format suivant : 
 * Centre : centre_, direction : direction_
 * 
 * @param st : le flux sur lequel on veut afficher le rayon
 * @param r : référence du rayon dont on veut afficher les informations
 * 
 * @return la référence vers le flux modifié
*/
std::ostream & operator << (std::ostream & st, const Ray3f & r) ;


#endif