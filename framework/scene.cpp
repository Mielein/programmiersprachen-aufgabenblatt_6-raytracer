#include "scene.hpp"


Scene sdfParser(std::string const& file){

/*     if(argc < 2){
        std::cout<<"Usage: "<<argv[0]<<"<PATH_TOSDF_FILE:string"<<std::endl;
        return -1;
    }
    std::string const in_file_path = argv[1]; */

    //open file in read-only && ASCII mode
    std::ifstream in_file("in_file_path", std::ios::in);
    std::string line_buffer;
    int32_t line_count = 0;
    std::string identifier;
    std::string class_name;

    while(std::getline(in_file, line_buffer)){
        //std::cout<<++line_count<<": "<<line_buffer<<std::endl;
        //construct stringstream using line_buffer string
        std::istringstream in_sstream(line_buffer);
        in_sstream>>identifier;
        std::cout<<"Identifier content: "<<identifier<<std::endl;

        //check for shapes / material / lights
        if("define" == identifier){
            in_sstream>>class_name;
            //check for shape type, then: parse attributes (including material lookup)
        }
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

            std::cout << ka_red <<" "<<ka_green<<" "<<ka_blue<<std::endl;
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
        }
        if("camera" == class_name){
            std::string camera_name;
            glm::vec3 pos, direction;
            unsigned int foxV;

            in_sstream >> camera_name;
            in_sstream >> pos.x;
            in_sstream >> pos.y;
            in_sstream >> pos.z;
            in_sstream >> direction.x;
            in_sstream >> direction.y;
            in_sstream >> direction.z;
            in_sstream >> foxV;
        }
        if("shape" == identifier){
            std::cout<<"Identifier: "<<identifier<<std::endl;
            if("sphere" == class_name){
                std::string sphere_name;
                float radius;
                glm::vec3 mid;
                std::string mat_name;

                in_sstream >> sphere_name;
                in_sstream >> radius;
                in_sstream >> mid.x;
                in_sstream >> mid.y;
                in_sstream >> mid.z;
                in_sstream >> mat_name;
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
            }
        }
        if("ambient" == class_name){
            std::string ambient_name;
            float clr_r, clr_g, clr_b;

            in_sstream >> ambient_name;
            in_sstream >> clr_r;
            in_sstream >> clr_g;
            in_sstream >> clr_b;
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