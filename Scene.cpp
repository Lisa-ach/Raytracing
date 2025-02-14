#include "Scene.h"
#include "Ray3f.h"
#include "Camera.h"
#include "Shape.h"
#include "Sdl.h"
#include "Quad.h"
#include <algorithm>
#include <random>
// #include <omp.h>
#include <stdio.h>

#ifndef M_PI
# define M_PI 3.1415926535
#endif

std::default_random_engine engine ;
std::uniform_real_distribution<double> uniform(0,1) ;

Scene::Scene(Camera camera, std::vector<Shape*> shapes, Ray3f source) {
    camera_ = camera;
    shapes_ = shapes;
    source_ = source;
}

Scene::Scene(const Scene& s) {
    camera_ = s.get_camera();
    shapes_ = s.get_shapes();
    source_ = s.get_source();
}

Scene& Scene::operator=(const Scene& s) {
    if (this != &s) {
        camera_ = s.get_camera();
        shapes_ = s.get_shapes();
        source_ = s.get_source();
    }
    return *this;
}

std::ostream & operator<<(std::ostream& st, const Scene& s) {
    st << "Camera : " << s.get_camera() << std::endl ;
    st << "Source : " << s.get_source() << std::endl ;
    st << "Shapes : " << std::endl ;

    std::vector<Shape*> shapes = s.get_shapes() ;
    for (const Shape* shape : shapes) {
        st << *shape << std::endl ;
    }
    return st ;
}

bool Scene::intersection (const Ray3f & d, Vector3f * P, Vector3f * N, int * shape_id, float * min_t) const {
    bool has_inter = false ;
    // On va stocker dans min_t le point d'intersection le plus proche
    *min_t = 1E10f ;
    // Pour chaque objet, on appelle la fonction is_hit
    // S'il y a intersection, has_inter passe à true
    // et on récupère le point d'intersection le plus proche
    for (size_t i = 0;i < shapes_.size();i++){
        Vector3f localP, localN ;
        float t ;
        int local_has_inter = shapes_[i]->is_hit(d,&localP,&localN,&t);
        if (local_has_inter == 1){
            has_inter = true ;
                if(t < *min_t){
                    *min_t = t ;
                    *P = localP ;
                    *N = localN ;
                    *shape_id = static_cast<int>(i);
                    // A la fin, on aura bien le vecteur normale N à la sphère la plus proche
                    // Le point d'intersection P, et l'id de la sphère
                }
         }
    }
    return has_inter ;
}

const float INTENSITE_LUMIERE = 3000000000.0f ;

Material Scene::get_color(const Ray3f & ray, int nb_rebonds) const {

    if (nb_rebonds == 0){
        return Material(0.0f,0.0f,0.0f,0.0f) ;
    }

    // N est le vecteur normal à la sphère en ce point, si intersection
    // P est le point d'intersection avec la sphère, si intersection
    // Ces vecteurs prendront des valeurs dans la fonction is_hit
    Vector3f P,N ;

    // Numéro de la sphère intersectée dans sphère
    // Le numéro sera trouvée avec la fonction scene::intersection
    int shape_id ;
    float t ;
    bool has_inter = intersection(ray,&P,&N,&shape_id,&t) ;       
    // Pour chaque pixel, on regarde s'il y a intersection avec la sphère
    // Si oui, on remplit ce pixel, en prenant bien en compte la source de lumière
    Material intensite_pixel(0.0f,0.0f,0.0f,0.0f) ;
    // -- A utiliser si utilisation de l'éclairage indirect
    // if (ray.get_direction() == Vector3f (0.0f)){
    //     has_inter = false ;
    // }
    // else 
    if (has_inter) {
        if (shapes_[shape_id]->get_miroir()){
            Vector3f direction_miroir = ray.get_direction() - 2 * dot(N,ray.get_direction())*N ;
            Ray3f rayon_miroir(P + 0.01*N, direction_miroir) ;
            intensite_pixel = get_color(rayon_miroir,nb_rebonds-1);
        }
        else {
            // Vecteur qui va du point d'intersection sphère-rayon à la source de lumière
            Vector3f L = source_.get_centre() - P ;

            // -- Code pour faire apparaitre les ombres
            // On trace un rayon qui part du point d'intersection vers la lumière
            // On regarde s'il s'intersecte avec un autre objet avant d'arriver à la lumière
            // Si oui, il est l'ombre d'un objet, et donc on lui met un pixel noir
            Ray3f ray_light(P+0.01f*N,L.get_normalised()) ;
            Vector3f P_light, N_light ;
            int sphere_id_light ;
            float t_light ;
            bool has_inter_light = intersection(ray_light,&P_light,&N_light,&sphere_id_light,&t_light) ;
            double d_light2 = L.norme2() ;
            if (has_inter_light && t_light*t_light < d_light2){
                intensite_pixel = Material(0.0f,0.0f,0.0f,0.0f) ;
            }
            else {
                // -- Contribution de l'éclairage direct
                // -- Modèle d'éclairage lambertien
   
                // Calcul intensité du pixel
                float cos_theta = std::max(0.0f, dot(L.get_normalised(), N));

                Vector3f intensite_pixel_vector = shapes_[shape_id]->get_albedo() * INTENSITE_LUMIERE * cos_theta /d_light2 ;
                intensite_pixel = Material(1.0f,1.0f,1.0f,0.0f) * intensite_pixel_vector;

                // -- Contribution de l'éclairage indirect
                // L'éclairage indirect va permettre d'avoir un rendu plus réaliste, des ombres plus douces

                // double r1 = uniform(engine) ;
                // double r2 = uniform(engine) ;
                // Vector3f direction_aleatoire_repere_local(static_cast<float>(cos(2*M_PI*r1)*sqrt(1-r2)),static_cast<float>(sin(2*M_PI*r1)*sqrt(1-r2)),static_cast<float>(sqrt(r2))) ;
                // Vector3f aleatoire(uniform(engine)-0.5,uniform(engine)-0.5,uniform(engine)-0.5) ;
                // Vector3f tangent1 = cross(N,aleatoire) ; tangent1.normalize() ;
                // Vector3f tangent2 = cross (tangent1, N) ;

                // Vector3f direction_aleatoire = direction_aleatoire_repere_local.get_z() * N + direction_aleatoire_repere_local.get_x() * tangent1 + 
                //     direction_aleatoire_repere_local.get_y() * tangent2 ;

                // Ray3f rayon_aleatoire(P + 0.001*N,direction_aleatoire) ;

                // intensite_pixel += get_color (rayon_aleatoire,nb_rebonds - 1)* shapes_[shape_id]->get_albedo() ;
            }
        }
    }
    return intensite_pixel ;
}


void Scene::render(int largeur, int hauteur, const std::string & filename){
    // On crée l'objet sdl
    Sdl sdl(largeur, hauteur, filename);

    if (!sdl.isValid()) {
        std::cerr << "Erreur lors de l'initialisation de SDL." << std::endl ;
        return ;
    }

    SDL_Renderer* renderer = sdl.getRenderer();

    // -- Partie à utiliser si utilisation de l'éclairage indirect
    // int nrays = 30 ;
    // --

    // Sert pour enregistrer l'image
    SDL_Surface *surface = SDL_CreateRGBSurface(0, largeur, hauteur, 32, 0, 0, 0, 0);

    // On parcourt chaque pixel
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {

            // Point correspondant au pixel
            Vector3f worldPoint(x, y, 0);

            // Vecteur qui part de la caméra et qui va jusqu'au pixel
            Vector3f direction_camera = Vector3f(x-camera_.get_position().get_x(),y-camera_.get_position().get_y(),-camera_.get_position().get_z()); // -largeur / (2.0 * tan(fov / 2.0)));
            // On le normalise
            direction_camera.normalize();
            
            // Rayon qui part de la caméra dont la direction est vers le pixel
            Ray3f ray(camera_.get_position(), direction_camera);

            Material color = get_color(ray,5) ;

            // -- Partie à utiliser si utilisation de l'éclairage indirect
            // Material color(0.0f,0.0f,0.0f,0.0f) ;
            // // #pragma omp parallel for
            // for (int k = 0 ; k < nrays ; k++){
            //     color += get_color(ray,5) ;
            // }
            // color /= static_cast<float>(nrays) ;
            // --

            // On remplit le pixel de couleur
            // On limite les composantes de couleur entre 0 et 255
            // + correction Gamma
            float r = std::min(255.0, std::max(0.0, std::pow(static_cast<double>(color.get_r()),1/2.2)));
            float g = std::min(255.0, std::max(0.0, std::pow(static_cast<double>(color.get_g()),1/2.2)));
            float b = std::min(255.0, std::max(0.0, std::pow(static_cast<double>(color.get_b()),1/2.2)));
            SDL_SetRenderDrawColor(renderer,r,g,b, 255);

            // SDL_SetRenderDrawColor(renderer,color.get_r(),color.get_g(),color.get_b(), 255);
            SDL_RenderDrawPoint(renderer, x, y);

            // Sert pour l'enregistrement de l'image
            Uint32 pixelColor = SDL_MapRGB(surface->format, color.get_r(), color.get_g(), color.get_b());
            int pixelIndex = x + y * largeur;
            Uint32 *pixels = static_cast<Uint32 *>(surface->pixels);
            pixels[pixelIndex] = pixelColor;

            }
        }

    // Maj de l'affichage
    SDL_RenderPresent(renderer);

    // Enregistrement de l'image
    SDL_SaveBMP(surface, filename.c_str());
    
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { // si la fenêtre est fermée
                quit = true ; // fin de la boucle
            }
        }
    }
} 