#ifndef SHAPE_H
#define SHAPE_H

#include "Material.h"
#include "Ray3f.h"
#include <cmath>
#include <ostream>

/**
 * @brief La classe Shape est la classe mère des classes Quad et Sphere
 * 
 * Elle permet de regrouper les différentes formes sous une même classe et 
 * ainsi d'avoir des attributs et des fonctions en commun
*/
class Shape {
    private :
        /**
         * @brief Le matériel de la forme
         * @see Material
        */
        Material matter_ ;
        /**
         * @brief Permet de savoir si la forme réfléchie la lumière ou non
         * 
         * Si miroir est true, la forme réfléchit la lumière et fait office de miroir.
         * Sinon, la forme est mat et ne réfléchit pas la lumière.
        */
        bool miroir_ ;

    public :
        /**
         * @brief Constructeur par défaut
         * 
         * Crée une instance de la classe Shape avec matter_ comme le matériel par défaut et 
         * miroir à false
         * @see Material
        */
        Shape() ; 
        /**
         * @brief Constructeur paramétré
         * 
         * Crée une instance de la classe Shape à partir des paramètres donnés
         * 
         * @param matter : le matériel voulu de la forme
         * @param miroir : si on veut que la forme soit miroir ou non
         * @see Material
        */
        Shape (Material matter, bool miroir); 

        /**
         * @brief Getter de l'attribut matter_
         * 
         * @return L'attribut matter_ de la classe
        */
        Material get_matter() const {return matter_ ;} ;
        /**
         * @brief Getter de l'attribut miroir_
         * 
         * @return L'attribut miroir_ de la classe
        */
        bool get_miroir() const { return miroir_ ;};
        /**
         * @brief Donne la valeur d'albédo du matériel comprise entre 0 et 1 pour chaque composante. Fonction utile pour l'éclairage direct.
         * @ref Rapport.pdf
         * 
         * @return L'albédo de matter_
        */
        Vector3f get_albedo() const {return (Vector3f (matter_.get_r()/255,matter_.get_g()/255 ,3*matter_.get_b()/255));}
        
        /**
         * @brief Vérifie si le rayon intersecte la forme
         * 
         * La fonction permet aussi de récupérer le point P d'intersection du rayon, la normale N
         * à ce point et la valeur de t à ce point.
         * Méthode virtuelle à implémenter dans les classes filles
         * @see Sphere, Quad
         * 
         * @param ray : le rayon avec lequel on veut voir s'il y a intersection
         * @param P : pointeur vers le point d'intersection entre le rayon et la forme
         * @param N : pointeur vers la normale associé au point P
         * @param t : pointeur vers la valeur de t au point P
         * @see Vector3f, Ray3f
         * 
         * @return 1 s'il y a intersection, 0 sinon
        */
        virtual int is_hit (Ray3f ray,Vector3f * P, Vector3f *N,float * t) = 0 ;

} ;

/**
 * @brief L'opérateur << pour afficher les informations de la forme
 * 
 * Affiche les informations de la scène donnée sous le format suivant : 
 * Shapes : [matter_ , miroir_]
 * 
 * @param st : le flux sur lequel on veut afficher la forme
 * @param s : référence de la forme dont on veut afficher les informations
 * 
 * @return la référence vers le flux modifié
*/
std::ostream & operator << (std::ostream & st, const Shape & s ) ;


#endif