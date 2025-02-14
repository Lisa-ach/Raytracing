#ifndef MATERIAL_H
#define MATERIAL_H

#include <cmath>
#include <ostream>
#include "Vector3f.h"


/**
 * @brief La classe définit la couleur ainsi que la brillance des objets de la scène 
 * 
 * Elle permet, pour chaque objet dans la scène, d'avoir une couleur et une brillance que l'utilisateur n'est pas
 * obligé de redéfinir à chaque fois. La couleur est définie par le système RGB et 
 * la brillance vaut entre 0 et 255
*/
class Material {
    private:
        /**
         * @brief Le composant rouge du matériel
         * 
         * Le composant est compris entre 0 et 255
        */
        float r_;
        /**
         * @brief Le composant vert du matériel
         * 
         * Le composant est compris entre 0 et 255
        */
        float g_;
        /**
         * @brief Le composant bleu du matériel
         * 
         * Le composant est compris entre 0 et 255
        */
        float b_;
        /**
         * @brief La brillance du matériel
         * 
         * Le composant est compris entre 0 et 255, 0 étant complétement mat et 255 réfléchissant complétement
         * la lumière
        */
        float shininess_ ;
    
    public:

        /**
         * @brief Constructeur par défaut
         * 
         * Par défaut la couleur du matériel est noir (0,0,0) et il est complétement mat (shininess à 0)
        */
        Material() ;
        /**
         * @brief Constructeur paramétré
         * 
         * Crée une instance de Material avec des paramètres en entrée
         * 
         * @param r : la quantité de rouge 
         * @param g : la quantité de vert
         * @param b : la quantité de bleu
         * @param shininess : la brillance
        */
        Material(float r, float g, float b, float shininess) ; 
        /**
         * @brief Constructeur de copie
         * 
         * Crée une instance de Material en copiant les attributs du Material donné un entrée
         * 
         * @param m : une référence vers le Material dont on veut faire la copie
        */
        Material (const Material & m); // c-c

        /**
         * @brief Getter de l'attribut r_
         * 
         * @return L'attribut r_ de la classe
        */
        float get_r() const { return r_; }
        /**
         * @brief Getter de l'attribut g_
         * 
         * @return L'attribut g_ de la classe
        */
        float get_g() const { return g_; }
        /**
         * @brief Getter de l'attribut b_
         * 
         * @return L'attribut b_ de la classe
        */
        float get_b() const { return b_; }
        /**
         * @brief Getter de l'attribut shininess_
         * 
         * @return L'attribut shininess_ de la classe
        */
        float get_shininess() const { return shininess_; }

        /**
         * @brief Setter de l'attribut r_
         * 
         * @param r : la quantité de rouge que l'on veut donner au matériel
        */
        void set_r(float r) { r_ = r; }
        /**
         * @brief Setter de l'attribut g_
         * 
         * @param g : la quantité de vert que l'on veut donner au matériel
        */
        void set_g(float g) { g_ = g; }
        /**
         * @brief Setter de l'attribut b_
         * 
         * @param b : la quantité de bleu que l'on veut donner au matériel
        */
        void set_b(float b) { b_ = b; }
        /**
         * @brief Setter de l'attribut shininess_
         * 
         * @param shininess : la brillance que l'on veut donner au matériel
        */
        void set_shininess(float shininess) { shininess_ = shininess ; }

        /**
         * @brief L'opérateur = de la classe
         * 
         * @param v : référence vers le matériel que l'on veut attribuer
         * 
         * @return Référence vers le matériel attribué
        */
        Material & operator= (const Material & v) ;
        /**
         * @brief L'opérateur += de la classe
         * 
         * @param v : référence vers le matériel que l'on veut ajouter
         * 
         * @return Référence vers le matériel nouvellement ajouté
        */
        Material & operator+=(const Material & v);
        /**
         * @brief L'opérateur -= de la classe
         * 
         * @param v : référence vers le matériel que l'on veut enlever
         * 
         * @return Référence vers le matériel nouvellement enlevé
        */
        Material & operator-=(const Material & v);
        /**
         * @brief L'opérateur *= de la classe
         * 
         * @param v : référence vers le matériel que l'on veut multiplier
         * 
         * @return Référence vers le matériel nouvellement multiplié
        */
        Material & operator*=(const Material & v);
        /**
         * @brief L'opérateur /= de la classe avec un autre matériel
         * 
         * @param v : référence vers le matériel que l'on veut diviser
         * 
         * @return Référence vers le matériel nouvellement divisé
        */
        Material & operator/=(const Material & v);
        /**
         * @brief L'opérateur /= de la classe avec un float
         * 
         * @param v : valeur du float avec lequel on veut diviser le matériel
         * 
         * @return Référence vers le matériel nouvellement divisé
        */
        Material & operator/=(const float v);


};

/**
 * @brief L'opérateur * de la classe avec un vecteur
 * 
 * Les 2 opérateurs suivants retournent la même valeur
 * 
 * @param v : le vecteur avec lequel on veut multiplier le matériel
 * @param m : le matériel que l'on veut multiplier
 * 
 * @return Un nouveau matériel qui est le résultat de la multiplication
*/
Material operator* (const Vector3f & v, const Material & m) ;
Material operator* (const Material & m, const Vector3f & v) ;

/**
 * @brief L'opérateur / de la classe avec un float
 *
 * @param m : le matériel que l'on veut diviser
 * @param v : le float avec lequel on veut diviser le matériel
 * 
 * @return Un nouveau matériel qui est le résultat de la division
*/
Material operator/ (const Material & m, const float v) ;

/**
 * @brief L'opérateur << pour afficher les informations du matériel
 * 
 * Affiche les informations du matériel donné sous le format suivant : 
 * RBG : (r_,g_,b_) ; Shinines : shininess_
 * 
 * @param st : le flux sur lequel on veut afficher le matériel
 * @param m : référence du matériel dont on veut afficher les informations
 * 
 * @return la référence vers le flux modifié
*/
std::ostream & operator << (std::ostream & st, const Material & m) ;


#endif