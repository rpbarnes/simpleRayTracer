#include <iostream>
#include <fstream>
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "lambertian.h"


vec3 color(const ray& r, hitable *world) {
    hit_record rec;

    if (world->hit(r, 0.0001, MAXFLOAT, rec)) {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5*color( ray(rec.p, target-rec.p), world);
    }
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}


int main() {
    std::ofstream myfile;
    myfile.open("example.ppm");
   
    int nx = 400;
    int ny = 200;
    int ns = 100;
    
    myfile << "P3\n" << nx << " " << ny << "\n255\n";

    int list_size = 2;
    hitable *list[list_size];
    list[0] = new sphere(vec3(0,0,-1), 0.5);
    list[1] = new sphere(vec3(0,-100.5,-1), 100);
    hitable *world = new hitable_list(list, list_size);
    camera cam;
    
    for (int j = ny-1; j >= 0; j--){
        for(int i = 0; i < nx; i++){
            vec3 col(0,0,0);
            for (int s = 0; s < ns; s++)
            {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);

                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world);
            }
            
            std::cout << col << std::endl;
            col /= float(ns);
            col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            myfile << ir << " " << ig << " " << ib << "\n";

        }
    }

    myfile.close();
}
