#include "scene.hpp"


Scene sdfParser(std::string const& file){

    //open file in read-only && ASCII mode
    std::ifstream in_file;
    in_file.open(file);
    std::string line_buffer;

    std::string identifier;
    std::string class_name;

    std::vector<std::shared_ptr<Shape>> shape_vec; 
    std::vector<std::shared_ptr<Light>> light_vec;
    std::map<std::string,std::shared_ptr<Material>> mat_map;

    Scene s;

    while(std::getline(in_file, line_buffer)){
        //std::cout<<++line_count<<": "<<line_buffer<<std::endl;
        //construct stringstream using line_buffer string
        std::istringstream in_sstream(line_buffer);
        in_sstream >> identifier;
        std::cout<<"Identifier content: "<<identifier<<std::endl;

        //check for shapes / material / lights
        if("define" == identifier){
            in_sstream>>class_name;
            //check for shape type, then: parse attributes (including material lookup)
        
            if("material" == class_name){
                //parse material attributes
                std::string material_name;
                //ka -> ambiente
                //kd -> spiegeld
                //ks -> reflexion
                float ka_red, ka_green, ka_blue;
                float kd_red, kd_green, kd_blue;
                float ks_red, ks_green, ks_blue;
                float m;

                in_sstream >> material_name;
                in_sstream >> ka_red >> ka_green >> ka_blue; 
                in_sstream >> kd_red >> kd_green >> kd_blue;
                in_sstream >> ks_red >> ks_green >> ks_blue;
                in_sstream >> m;

                std::cout << ka_red <<" "<<ka_green<<" "<<ka_blue<<std::endl;
                std::cout << kd_red <<" "<<kd_green<<" "<<kd_blue<<std::endl;
                std::cout << ks_red <<" "<<ks_green<<" "<<ks_blue<<std::endl;
                std::cout << m << std::endl;

                Material mat(material_name,{ka_red,ka_green,ka_blue},{kd_red,kd_green,kd_blue},{ks_red,ks_green,ks_blue},m);
                auto mat_ptr = std::make_shared<Material>(mat);
                s.mat_map.insert({material_name, mat_ptr}); 
            }
            if("light" == class_name){
                std::string light_name;
                float clr_r, clr_g, clr_b;
                glm::vec3 pos;
                float brightness;

                in_sstream >> light_name;
                in_sstream >> clr_r;
                in_sstream >> clr_g;
                in_sstream >> clr_b;
                in_sstream >> pos.x;
                in_sstream >> pos.y;
                in_sstream >> pos.z;
                in_sstream >> brightness;

                Light light(light_name,{pos.x,pos.y,pos.z},{clr_r,clr_g,clr_b},brightness);
                auto light_ptr = std::make_shared<Light>(light);
                s.light_vec.push_back(light_ptr);                  
            }
            if("camera" == class_name){
                std::string camera_name;
                glm::vec3 pos, direction;
                unsigned int fovX;

                in_sstream >> camera_name;
                in_sstream >> pos.x;
                in_sstream >> pos.y;
                in_sstream >> pos.z;
                in_sstream >> direction.x;
                in_sstream >> direction.y;
                in_sstream >> direction.z;
                in_sstream >> fovX;

                Camera cam({camera_name, {pos.x, pos.y, pos.z}, {direction.x, direction.y, direction.z}, fovX});

            }
            if("shape" == class_name){
                if("sphere" == class_name){
                    std::string sphere_name;
                    float clr_r,clr_g,clr_b;
                    float radius;
                    glm::vec3 mid;
                    std::string mat_name;

                    in_sstream >> sphere_name;
                    in_sstream >> clr_r;
                    in_sstream >> clr_g;
                    in_sstream >> clr_b;
                    in_sstream >> radius;
                    in_sstream >> mid.x;
                    in_sstream >> mid.y;
                    in_sstream >> mid.z;
                    in_sstream >> mat_name;

                    auto mat1 = mat_map.find(mat_name);
                    Sphere sphere(sphere_name,{clr_r,clr_g,clr_b},mat1->second,{mid.x,mid.y,mid.z},radius);
                    std::shared_ptr<Shape> sphere_ptr = std::make_shared<Sphere>(sphere);                    
                    s.shape_vec.push_back(sphere_ptr); 
                }
                if("box" == class_name){
                    std::string box_name;
                    float clr_r, clr_g, clr_b;
                    glm::vec3 min;
                    glm::vec3 max;
                    std::string mat_name;

                    in_sstream >> box_name;
                    in_sstream >> clr_r;
                    in_sstream >> clr_g;
                    in_sstream >> clr_b;
                    in_sstream >> min.x;
                    in_sstream >> min.y;
                    in_sstream >> min.z;
                    in_sstream >> max.x;
                    in_sstream >> max.y;
                    in_sstream >> max.z;
                    in_sstream >> mat_name;

                    auto mat2 = mat_map.find(mat_name);
                    Box box({min.x,min.y,min.z},{max.x,max.y,max.z},box_name,{clr_r,clr_g,clr_b},mat2->second);
                    std::shared_ptr<Shape> box_ptr = std::make_shared<Box>(box);
                    s.shape_vec.push_back(box_ptr); 
                }
                
            }
            if("ambient" == class_name){
                std::string ambient_name;
                float clr_r, clr_g, clr_b;

                in_sstream >> ambient_name;
                in_sstream >> clr_r;
                in_sstream >> clr_g;
                in_sstream >> clr_b;
                Ambient amby({ambient_name, {clr_r, clr_g, clr_b}});
                s.background_ = amby;
            }
            if("render" == class_name){
                std::string render_name;
                std::string cam_name;
                std::string filename;
                unsigned width;                                           
                unsigned height;

                in_sstream >> render_name;
                in_sstream >> cam_name;
                in_sstream >> filename;
                in_sstream >> width;
                in_sstream >> height;
            }
            else {
                std::cout<<"Line was not valid!"<<std::endl;
            }
        }
    }
    return s;
}
