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
        //std::cout<<++line_count<<": "<<line_buffer<<std::endl;
        //construct stringstream using line_buffer string
        //std::cout<<"reading new line"<<std::endl;
        std::istringstream in_sstream(line_buffer);
        in_sstream >> identifier;
        //std::cout<<"Identifier content: "<<identifier<<std::endl;

        //check for shapes / material / lights
        if("define" == identifier){
            in_sstream>>class_name;
            //std::cout<<"class content: "<<class_name<<std::endl;
            //check for shape type, then: parse attributes (including material lookup)
        
            if("material" == class_name){
                //parse material attributes
                std::string material_name;
                //ka -> ambient
                //kd -> diffuse
                //ks -> specular
                float ka_red, ka_green, ka_blue;
                float kd_red, kd_green, kd_blue;
                float ks_red, ks_green, ks_blue;
                float m;
                float mirror;

                in_sstream >> material_name;
                in_sstream >> ka_red >> ka_green >> ka_blue; 
                in_sstream >> kd_red >> kd_green >> kd_blue;
                in_sstream >> ks_red >> ks_green >> ks_blue;
                in_sstream >> m;
                in_sstream >> mirror;

/*              std::cout << material_name<<std::endl;
                std::cout << ka_red <<" "<<ka_green<<" "<<ka_blue<<std::endl;
                std::cout << kd_red <<" "<<kd_green<<" "<<kd_blue<<std::endl;
                std::cout << ks_red <<" "<<ks_green<<" "<<ks_blue<<std::endl;
                std::cout << m << std::endl; */

                Material mat(material_name,{ka_red,ka_green,ka_blue},{kd_red,kd_green,kd_blue},{ks_red,ks_green,ks_blue},m, mirror);
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

/*                 std::cout<<light_name<<std::endl;
                std::cout<<clr_r<<" "<<clr_g<<" "<<clr_b<<std::endl;
                std::cout<<pos.x<<" "<<pos.y<<" "<<pos.z<<std::endl; 
                std::cout<<brightness<<std::endl;   */              
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

                //std::cout<<camera_name<<std::endl;
/*                 std::cout<<cam.pos_.x<<" "<<cam.pos_.y<<" "<<cam.pos_.z<<std::endl;
                std::cout<<cam.direction_.x<<" "<<cam.direction_.y<<" "<<cam.direction_.z<<std::endl;  
                std::cout<<fovX<<std::endl;   */
                s.camera_.name_ = camera_name;
                s.camera_.fovX = fovX;
                s.camera_.pos_ = eye;
                s.camera_.direction_ = dir;
                s.camera_.up_ = up;
                
            }
            if("shape" == class_name){
                in_sstream>>class_name;
                if("sphere" == class_name){
                    std::cout<<"class content: "<<class_name<<std::endl;
                    std::string sphere_name;
                    /* float clr_r,clr_g,clr_b; */
                    float radius;
                    glm::vec3 mid;
                    std::string mat_name;

                    in_sstream >> sphere_name;
/*                     in_sstream >> clr_r;
                    in_sstream >> clr_g;
                    in_sstream >> clr_b;
                     */
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

/*                     std::cout<<sphere_name<<std::endl;
                    std::cout<<clr_r<<" "<<clr_g<<" "<<clr_b<<std::endl;
                    std::cout<<radius<<std::endl;
                    std::cout<<mid.x<<" "<<mid.y<<" "<<mid.z<<std::endl; 
                    std::cout<<mat_name<<std::endl;  */
                }
                if("box" == class_name){
                    std::cout<<"class content: "<<class_name<<std::endl;
                    std::string box_name;
                    /* float clr_r, clr_g, clr_b; */
                    glm::vec3 min;
                    glm::vec3 max;
                    std::string mat_name;

                    in_sstream >> box_name;
/*                     in_sstream >> clr_r;
                    in_sstream >> clr_g;
                    in_sstream >> clr_b;  */
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
 
/*                     std::cout<<box_name<<std::endl;
                    std::cout<<clr_r<<" "<<clr_g<<" "<<clr_b<<std::endl; 
                    std::cout<<min.x<<" "<<min.y<<" "<<min.z<<std::endl;
                    std::cout<<max.x<<" "<<max.y<<" "<<max.z<<std::endl; 
                    std::cout<<mat_name<<std::endl;  */
                }
                if("triangle" == class_name){
                    std::cout<<"class content: "<<class_name<<std::endl;
                    std::string triangle_name;
                    /* float clr_r, clr_g, clr_b; */
                    glm::vec3 a;
                    glm::vec3 b;
                    glm::vec3 c;
                    std::string mat_name;

                    in_sstream >> triangle_name;
/*                     in_sstream >> clr_r;
                    in_sstream >> clr_g;
                    in_sstream >> clr_b;  */
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
/*             else {
                std::cout<<"Line was not valid!"<<std::endl;
            } */
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

/*             std::cout<<ambient_name<<std::endl; 
            std::cout<<clr_r<<" "<<clr_g<<" "<<clr_b<<std::endl;  */
        }
        if("transform" == identifier){
            std::cout<<"identifier content: "<<identifier<<std::endl;
            std::string transOb_name;
            std::string transformation;
            float x,y,z,angle;
            in_sstream >> transOb_name;
            in_sstream >> transformation;
            in_sstream >> x;
            in_sstream >> y;
            in_sstream >> z;

            if("scale" == transformation){
                std::cout<<"transformation: "<<transformation<<std::endl;

                glm::mat4 mat = glm::mat4{
                    glm::vec4{x,0.0f,0.0f,0.0f},
                    glm::vec4{0.0f,y,0.0f,0.0f},
                    glm::vec4{0.0f,0.0f,z,0.0f},
                    glm::vec4{0.0f,0.0f,0.0f,1.0f}                   
                };
                for(auto shape : s.shape_vec){
                    shape->transformation(mat);
                }
            }
            if("translate" == transformation){
                std::cout<<"transformation: "<<transformation<<std::endl;

                glm::mat4 mat = glm::mat4{
                    glm::vec4{1.0f,0.0f,0.0f,x},
                    glm::vec4{0.0f,1.0f,0.0f,y},
                    glm::vec4{0.0f,0.0f,1.0f,z},
                    glm::vec4{0.0f,0.0f,0.0f,1.0f}                    
                };
                for(auto shape : s.shape_vec){
                    shape->transformation(mat);
                }                
            }
            if("rotate" == transformation){
                std::cout<<"transformation: "<<transformation<<std::endl;

                in_sstream >> angle;
                if(x == 1){
                    glm::mat4 mat = glm::mat4{
                    glm::vec4{1.0f,0.0f,0.0f,0.0f},
                    glm::vec4{0.0f,cos(angle),-sin(angle),0.0f},
                    glm::vec4{0.0f,sin(angle),cos(angle),0.0f},
                    glm::vec4{0.0f,0.0f,0.0f,1.0f} 
                    }; 
                    for(auto shape : s.shape_vec){
                        shape->transformation(mat);
                    }                                       
                }
                if(y == 1){
                    glm::mat4 mat = glm::mat4{
                    glm::vec4{cos(angle),0.0f,-sin(angle),0.0f},
                    glm::vec4{0.0f,1.0f,0.0f,0.0f},
                    glm::vec4{sin(angle),0.0f,cos(angle),0.0},
                    glm::vec4{0.0f,0.0f,0.0f,1.0f}                    
                };
                    for(auto shape : s.shape_vec){
                        shape->transformation(mat);
                    }   
                }
                if(z == 1){
                    glm::mat4 mat = glm::mat4{
                    glm::vec4{cos(angle),-sin(angle),0.0f,0.0f},
                    glm::vec4{sin(angle),cos(angle),0.0f,0.0f},
                    glm::vec4{0.0f,0.0f,1.0f,0.0f},
                    glm::vec4{0.0f,0.0f,0.0f,1.0f},                    
                    };
                    for(auto shape : s.shape_vec){
                        shape->transformation(mat);
                    } 
                }
            }
        }
        if("render" == identifier){
            std::cout<<"identifier content: "<<identifier<<std::endl;
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

/*             std::cout<<render_name<<std::endl;
            std::cout<<cam_name<<std::endl;
            std::cout<<filename<<std::endl;
            std::cout<<width<<std::endl; 
            std::cout<<height<<std::endl; 
            std::cout<<depth<<std::endl;  */
            //s.camera_.name_ = cam_name;
            s.render_value.file = filename;
            s.render_value.w = width;
            s.render_value.h = height;
            s.render_value.depth = depth;

            
        }
    }
    return s;
}
