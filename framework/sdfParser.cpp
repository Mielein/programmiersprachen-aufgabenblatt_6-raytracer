#include <iostream> //debug prints
#include <fstream> //open / read / write / close files
#include <sstream> //stringstram -> easy parsing mechanics
#include <string> //buffer lines read from file
#include <glm/vec3.hpp>

int main(int argc, char** argv){

    if(argc < 2){
        std::cout<<"Usage: "<<argv[0]<<"<PATH_TOSDF_FILE:string"<<std::endl;
        return -1;
    }
    std::string const in_file_path = argv[1];

    //open file in read-only && ASCII mode
    std::ifstream in_file(in_file_path, std::ios::in);

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
        else if("material" == class_name){
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
        else if("light" == class_name){
            //TO-DO
            std::string light_name;
            in_sstream >> light_name;

            float clr_r, clr_g, clr_b;
            glm::vec3 pos;
            float brightness;

            in_sstream >> clr_r;
            in_sstream >> clr_g;
            in_sstream >> clr_b;
            in_sstream >> pos.x;
            in_sstream >> pos.y;
            in_sstream >> pos.z;
            in_sstream >> brightness;


        }
        else {
            std::cout<<"Line was not valid!"<<std::endl;
        }
    }
}