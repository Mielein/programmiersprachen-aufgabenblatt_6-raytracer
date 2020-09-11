#include "scene.hpp"


Scene sdfParser(std::string const& file){

    //open file in read-only && ASCII mode
    std::ifstream in_file;
    in_file.open(file);
    std::string line_buffer;
    std::string identifier;
    std::string class_name;

    Scene s;

    while(std::getline(in_file, line_buffer)){
        std::istringstream in_sstream(line_buffer);
        in_sstream >> identifier;

        if("define" == identifier){
            in_sstream>>class_name;

            if("material" == class_name){
                std::string material_name;

                float ka_red, ka_green, ka_blue;
                float kd_red, kd_green, kd_blue;
                float ks_red, ks_green, ks_blue;
                float m, mirror;

                in_sstream >> material_name;
                in_sstream >> ka_red >> ka_green >> ka_blue; 
                in_sstream >> kd_red >> kd_green >> kd_blue;
                in_sstream >> ks_red >> ks_green >> ks_blue;
                in_sstream >> m;
                in_sstream >> mirror;

                Material mat(material_name,{ka_red,ka_green,ka_blue},{kd_red,kd_green,kd_blue},{ks_red,ks_green,ks_blue},m,mirror);
                auto mat_ptr = std::make_shared<Material>(mat);
                s.mat_map.insert({material_name, mat_ptr}); 
            }
            if("light" == class_name){
                std::string light_name;
                float clr_r, clr_g, clr_b;
                glm::vec3 pos;
                float brightness;

                in_sstream >> light_name;
                in_sstream >> pos.x;
                in_sstream >> pos.y;
                in_sstream >> pos.z;
                in_sstream >> clr_r;
                in_sstream >> clr_g;
                in_sstream >> clr_b;
                in_sstream >> brightness;

                Light light(light_name,{pos.x,pos.y,pos.z},{clr_r,clr_g,clr_b},brightness);
                auto light_ptr = std::make_shared<Light>(light);
                s.light_vec.push_back(light_ptr);  

            }
            if("camera" == class_name){
                std::string camera_name;
                glm::vec3 eye, dir, up;
                unsigned int fovX;

                in_sstream >> camera_name;
                in_sstream >> fovX;
                in_sstream >> eye.x;
                in_sstream >> eye.y;
                in_sstream >> eye.z;
                in_sstream >> dir.x;
                in_sstream >> dir.y;
                in_sstream >> dir.z; 
                in_sstream >> up.x;
                in_sstream >> up.y;
                in_sstream >> up.z;

                s.camera_.name_ = camera_name;
                s.camera_.fovX = fovX;
                s.camera_.pos_ = eye;
                s.camera_.direction_ = dir;
                s.camera_.up_ = up;
                
            }
            if("shape" == class_name){
                in_sstream>>class_name;
                if("sphere" == class_name){
                    std::string sphere_name;
                    float radius;
                    glm::vec3 mid;
                    std::string mat_name;

                    in_sstream >> sphere_name;
                    in_sstream >> mid.x;
                    in_sstream >> mid.y;
                    in_sstream >> mid.z;
                    in_sstream >> radius;
                    in_sstream >> mat_name;

                    auto mat1 = s.mat_map.find(mat_name);
                    if (mat1 == s.mat_map.end()){
                        std::cerr << "Hier findet der doofe parser kein Material In einem Kreis" << std::endl;
                    }                    
                    Sphere sphere(sphere_name,{0.0f,0.0f,0.0f},mat1->second,{mid.x,mid.y,mid.z},radius);
                    std::shared_ptr<Shape> sphere_ptr = std::make_shared<Sphere>(sphere);                    
                    s.shape_vec.push_back(sphere_ptr); 

                }
                if("box" == class_name){
                    std::string box_name;
                    glm::vec3 min;
                    glm::vec3 max;
                    std::string mat_name;

                    in_sstream >> box_name;
                    in_sstream >> min.x;
                    in_sstream >> min.y;
                    in_sstream >> min.z;
                    in_sstream >> max.x;
                    in_sstream >> max.y;
                    in_sstream >> max.z;
                    in_sstream >> mat_name;

                    auto mat2 = s.mat_map.find(mat_name);
                    if (mat2 == s.mat_map.end()){
                        std::cerr << "Hier findet der doofe parser kein Material" << std::endl;
                    }
                    Box box({min.x,min.y,min.z},{max.x,max.y,max.z},box_name,{0.0f,0.0f,0.0f},mat2->second);
                    std::shared_ptr<Shape> box_ptr = std::make_shared<Box>(box);
                    s.shape_vec.push_back(box_ptr); 
 
                }
                if("triangle" == class_name){
                    std::string triangle_name;

                    glm::vec3 a;
                    glm::vec3 b;
                    glm::vec3 c;
                    std::string mat_name;

                    in_sstream >> triangle_name;
                    in_sstream >> a.x;
                    in_sstream >> a.y;
                    in_sstream >> a.z;
                    in_sstream >> b.x;
                    in_sstream >> b.y;
                    in_sstream >> b.z;
                    in_sstream >> c.x;
                    in_sstream >> c.y;
                    in_sstream >> c.z;                    
                    in_sstream >> mat_name;

                    auto mat3 = s.mat_map.find(mat_name);
                    if (mat3 == s.mat_map.end()){
                        std::cerr << "Hier findet der doofe parser kein Material" << std::endl;
                    }
                    Triangle triangle{triangle_name,mat3->second,a,b,c};
                    std::shared_ptr<Shape> tri_ptr = std::make_shared<Triangle>(triangle);
                    s.shape_vec.push_back(tri_ptr); 
                }    
            }
        }
        if("ambient" == identifier){
            std::string ambient_name; 
            float clr_r, clr_g, clr_b;

            in_sstream >> ambient_name; 
            in_sstream >> clr_r;
            in_sstream >> clr_g;
            in_sstream >> clr_b;

            void sdf_render(unsigned const& w, unsigned const& h, std::string const& file, unsigned const& depth);
            s.background_.color_.r = clr_r;
            s.background_.color_.g = clr_g;
            s.background_.color_.b = clr_b;
            s.background_.name_ = ambient_name;
        }
        if("transform" == identifier){
            std::string transOb_name;
            std::string transformation;
            float x,y,z,angle;
            in_sstream >> transOb_name;
            in_sstream >> transformation;
            in_sstream >> x;
            in_sstream >> y;
            in_sstream >> z;
            if("scale" == transformation){
                
                for(auto shape : s.shape_vec){
                    if (shape->getName() == transOb_name){
                        shape->scale({x,y,z});
                    }
                }
            }
            if("translate" == transformation){
                for(auto shape : s.shape_vec){
                    if (shape->getName() == transOb_name){
                        shape->translate({x,y,z});
                    }
                }                
            }
            if("rotate" == transformation){

                in_sstream >> angle;
                for(auto shape : s.shape_vec){
                    if (shape->getName() == transOb_name){
                        shape->rotate(angle,{x,y,z});
                    }
                }                
               
            }
        }
        if("render" == identifier){
            std::string render_name;
            std::string cam_name;
            std::string filename;
            unsigned width;                                           
            unsigned height;
            unsigned depth;

            in_sstream >> render_name;
            in_sstream >> cam_name;
            in_sstream >> filename;
            in_sstream >> width;
            in_sstream >> height;
            in_sstream >> depth;

            s.render_value.file = filename;
            s.render_value.w = width;
            s.render_value.h = height;
            s.render_value.depth = depth;
        }
    }
    return s;
}
