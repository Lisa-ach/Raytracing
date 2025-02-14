#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <cmath>
#include <ostream>

/**
 * @brief La classe définit les vecteurs à 3 dimensions que l'on utilisera dans le reste du projet
*/

class Vector3f {
    private:
        /**
         * @brief La valeur de l'axe des abscisses
        */
        float x_;
        /**
         * @brief La valeur de l'axe des ordonnées
        */
        float y_;
        /**
         * @brief La valeur de l'axe des cotes
        */
        float z_;
    
    public:

        /**
         * @brief Constructeur par défaut
         * 
         * Crée une instance de la classe Vector3f avec les 3 attributs de la classe à 0
        */
        Vector3f() ;
        /**
         * @brief Constructeur paramétré
         * 
         * Crée une instance de la classe Vector3f à partir des paramètres donnés
         * 
         * @param x : la valeur du vecteur sur l'axe des abscisses
         * @param y : la valeur du vecteur sur l'axe des ordonnées
         * @param z : la valeur du vecteur sur l'axe des cotes
        */
        Vector3f(float x, float y, float z) ;
        /**
         * @brief Constructeur paramétré
         * 
         * Crée une instance de la classe Vector3f à partir de la valeur de x, tous les attributs ayant la même valeur
         * 
         * @param x : la valeur de tous les éléments du vecteur
        */
        Vector3f(float x) ;
        /**
         * @brief Constructeur de copie
         * 
         * Crée une instance de Vector3f en copiant les attributs du Vector3f donné un entrée
         * 
         * @param q : une référence vers le Vector3f dont on veut faire la copie
         */
        Vector3f (const Vector3f & v);

        /**
         * @brief Getter de l'attribut x_
         * 
         * @return L'attribut x_ de la classe
        */
        float get_x() const { return x_; }
        /**
         * @brief Getter de l'attribut y_
         * 
         * @return L'attribut y_ de la classe
        */
        float get_y() const { return y_; }
        /**
         * @brief Getter de l'attribut z_
         * 
         * @return L'attribut z_ de la classe
        */
        float get_z() const { return z_; }

        /**
         * @brief Setter de l'attribut x_
         * 
         * @param x : la valeur de x que l'on veut donner au vecteur
        */
        void set_x(float x) { x_ = x ; }
        /**
         * @brief Setter de l'attribut y_
         * 
         * @param x : la valeur de y que l'on veut donner au vecteur
        */
        void set_y(float y) { y_ = y ; }
        /**
         * @brief Setter de l'attribut z_
         * 
         * @param x : la valeur de z que l'on veut donner au vecteur
        */
        void set_z(float z) { z_ = z ; }

        /**
         * @brief L'opérateur = de la classe
         * 
         * @param v : référence vers le vecteur que l'on veut attribuer
         * 
         * @return Référence vers le vecteur attribué
        */
        Vector3f & operator= (const Vector3f & v) ;
        /**
         * @brief L'opérateur += de la classe
         * 
         * @param v : référence vers le vecteur que l'on veut ajouter
         * 
         * @return Référence vers le vecteur nouvellement ajouté
        */
        Vector3f & operator+=(const Vector3f & v);
        /**
         * @brief L'opérateur -= de la classe
         * 
         * @param v : référence vers le vecteur que l'on veut enlever
         * 
         * @return Référence vers le vecteur nouvellement enlevé
        */
        Vector3f & operator-=(const Vector3f & v);
        /**
         * @brief L'opérateur *= de la classe
         * 
         * @param v : référence vers le vecteur que l'on veut multiplier
         * 
         * @return Référence vers le vecteur nouvellement multiplié
        */
        Vector3f & operator*=(const Vector3f & v);
        /**
         * @brief Fait le produit scalaire
         * 
         * @param v : référence vers le vecteur dont on veut avoir le produit scalaire
         * 
         * @return Valeur du produit scalaire
        */
        float  dot(const Vector3f & v);
        /**
         * @brief L'opérateur /= de la classe avec un autre vecteur
         * 
         * @param v : référence vers le vecteur que l'on veut diviser
         * 
         * @return Référence vers le vecteur nouvellement divisé
        */
        Vector3f & operator/=(const Vector3f & v);

        /**
         * @brief Donne la longueur du vecteur
         * 
         * @return La longueur du vecteur
        */
        float longueur() const {
            return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
        }

        /**
         * @brief Donne la norme 2 du vecteur
         * 
         * @return La norme 2 du vecteur
        */
        float norme2() const {
            return (x_ * x_ + y_ * y_ + z_ * z_);
        }

        /**
         * @brief Normalise le vecteur
        */
        void normalize() ;

        /**
         * @brief Donne une copie du vecteur normalisé
         * 
         * @return Un vecteur normalisé
        */
        Vector3f get_normalised() ;


};

/**
 * @brief L'opérateur == de la classe
 * 
 * @param v1 : référence vers le premier vecteur que l'on veut comparer
 * @param v2 : référence vers le deuxième vecteur que l'on veut comparer
 * 
 * @return true si les deux vecteurs sont égaux, false s'ils ne le sont pas
*/
bool operator== (const Vector3f & v1, const Vector3f & v2) ;

/**
 * @brief L'opérateur + de la classe
 * 
 * @param v1 : référence vers le premier vecteur que l'on veut ajouter
 * @param v2 : référence vers le deuxième vecteur que l'on veuts ajouter
 * 
 * @return Un nouveau vecteur qui est le résultat de l'addition
*/
Vector3f operator+ (const Vector3f & v1, const Vector3f & v2) ;
/**
 * @brief L'opérateur - de la classe
 * 
 * @param v1 : référence vers le premier vecteur que l'on veut soustraire
 * @param v2 : référence vers le deuxième vecteur que l'on veut soustraire
 * 
 * @return Un nouveau vecteur qui est le résultat de la soustraction
*/
Vector3f operator- (const Vector3f & v1, const Vector3f & v2) ;

/**
 * @brief L'opérateur * de la classe avec un autre vecteur
 * 
 * @param v1 : référence vers le premier vecteur que l'on veut multiplier
 * @param v2 : référence vers le deuxième vecteur que l'on veut multiplier
 * 
 * @return Un nouveau vecteur qui est le résultat de la multiplication
*/
Vector3f operator* (const Vector3f & v1, const Vector3f & v2) ;
/**
 * @brief L'opérateur * de la classe avec un float
 * 
 * @param v1 : le valeur du float avec lequel on veut multiplier le vecteur
 * @param v2 : référence vers le vecteur que l'on veut multiplier
 * 
 * @return Un nouveau vecteur qui est le résultat de la multiplication
*/
Vector3f operator* (const float v1, const Vector3f & v2) ;
/**
 * @brief L'opérateur / de la classe avec un autre vecteur
 * 
 * @param v1 : référence vers le premier vecteur que l'on veut diviser
 * @param v2 : référence vers le deuxième vecteur que l'on veut diviser
 * 
 * @return Un nouveau vecteur qui est le résultat de la division
*/
Vector3f operator/ (const Vector3f & v1, const Vector3f & v2) ;

/**
 * @brief Le produit scalaire entre 2 vecteurs
 * 
 * @param v1 : référence vers le premier vecteur 
 * @param v2 : référence vers le deuxième vecteur 
 * 
 * @return Le résultat du produit scalaire entre les deux vecteurs
*/
float dot (const Vector3f & v1, const Vector3f & v2) ;

/**
 * @brief Le produit vectoriel entre 2 vecteurs
 * 
 * @param v1 : référence vers le premier vecteur 
 * @param v2 : référence vers le deuxième vecteur 
 * 
 * @return Le résultat du produit vectoriel entre les deux vecteurs
*/
Vector3f cross (const Vector3f & v1, const Vector3f & v2);

/**
 * @brief L'opérateur << pour afficher les informations du vecteur
 * 
 * Affiche les informations du vecteur donné sous le format suivant : 
 * (x_, y_, z_)
 * 
 * @param st : le flux sur lequel on veut afficher le vecteur
 * @param v : référence du vecteur dont on veut afficher les informations
 * 
 * @return la référence vers le flux modifié
*/
std::ostream & operator << (std::ostream & st, const Vector3f & v) ;


#endif