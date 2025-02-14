#include "Vector3f.h"
#include "Ray3f.h"
#include "Camera.h"
#include "Material.h"
#include "Shape.h"
#include "Scene.h"
#include "Sphere.h"
#include "Quad.h"
#include <iostream>
#include <stdio.h>

using namespace std;

// g++ -g -Wall -Wextra -o projet *.cpp `pkg-config --cflags --libs sdl2`
// g++ -g -Wall -Wextra -fopenmp -o projet *.cpp `pkg-config --cflags --libs sdl2`

int main(int argc, char* argv[]) {

    (void)argc ; 
    (void)argv ;

    int SIZE_WINDOW = 500 ;

    cout << "Entrez la valeur d'un côté de la fenêtre voulue (entre 500 - 900 par exemple) : " << endl ;
    cout << "Size : " ; 
    cin >> SIZE_WINDOW ;

    // Les proportions des objets dans l'espace ont été réfléchies dans un carré de dimension 900
    // Pour connaitre les dimensions des objets dans un espace de taille différente, on applique un rapport
    float rapport = SIZE_WINDOW / 900.0 ;
 
    vector<Shape*> shapes;

    //-- Sphères
    // 1ère sphère
    Vector3f v(SIZE_WINDOW/3-25, SIZE_WINDOW/2, 60*rapport);
    Material m(255.0f, 0.0f, 0.0f,0.0f);
    shapes.push_back(new Sphere(m, v, 150.0f * rapport));
    // 2ème sphère
    Vector3f v2 (2*SIZE_WINDOW/3+25, SIZE_WINDOW/2, 400*rapport);
    shapes.push_back(new Sphere(m, v2, 150.0f * rapport,true));

    // Création des sphères qui vont représenter le sol, le plafond, le mur gauche, le mur droit, et le mur du fond
    // On prend des sphères avec des rayons très grands, et donc ça fera comme des plans visuellement
    int rayon_sph_murs = 6000 * rapport ;
    shapes.push_back(new Sphere(Material(255.0f, 255.0f, 255.0f, 0.0f), Vector3f(SIZE_WINDOW / 2, rayon_sph_murs + SIZE_WINDOW - 60 * rapport, 0), rayon_sph_murs)); // sol
    shapes.push_back(new Sphere(Material(255.0f, 0.0f, 0.0f, 0.0f), Vector3f(SIZE_WINDOW / 2, -rayon_sph_murs + 60 * rapport, 0), rayon_sph_murs)); // plafond
    shapes.push_back(new Sphere(Material(0.0f,255.0f,0.0f, 0.0f), Vector3f(-rayon_sph_murs + 60 * rapport, SIZE_WINDOW / 2, 0), rayon_sph_murs)); // mur gauche
    shapes.push_back(new Sphere(Material(0.0f,0.0f,255.0f, 0.0f), Vector3f(rayon_sph_murs + SIZE_WINDOW - 60 * rapport, SIZE_WINDOW / 2, 0), rayon_sph_murs)); // mur droit
    shapes.push_back(new Sphere(Material(192.0f, 192.0f, 192.0f, 0.0f), Vector3f(SIZE_WINDOW / 2, SIZE_WINDOW / 2, rayon_sph_murs + 500 * rapport), rayon_sph_murs)); // mur fond

    // -- Cube
    Material m_cube(255.0f, 255.0f, 0.0f,0.0f);
    Vector3f A(700.0f*rapport, 700.0f*rapport, 20.0f*rapport) ;
    Vector3f B(100.0f*rapport, 0.0f, 0.0f) ;
    Vector3f C(0.0f, 700.0f*rapport, 0.0f) ;
    shapes.push_back(new Quad(m_cube, A, B, C));

    // La caméra est placé à z = -1000*rapport
    // De ce fait, elle a assez de recul : la sphère n'est pas déformée
    Camera camera = Camera(Vector3f(SIZE_WINDOW/2,SIZE_WINDOW/2,-1000*rapport),Vector3f(0,0,-1));
	Ray3f source = Ray3f(Vector3f(SIZE_WINDOW / 2.0, 100.0f*rapport, 0.0f*rapport),Vector3f(0,1,0));

    Scene scene(camera,shapes,source);

    // Image produite et enregistrée
    scene.render(SIZE_WINDOW, SIZE_WINDOW, "Ma Fenêtre SDL");

    return 0;
}