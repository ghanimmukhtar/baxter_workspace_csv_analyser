#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/Dense>

std::vector<Eigen::Vector3d> processed_points, extracted_orientations;
std::vector<int> start_index, finish_index;


bool processed_point(Eigen::Vector3d current_point) {
    bool processed = false;
    for(int i = 0; i < processed_points.size(); i++)
        if (processed_points[i] == current_point) {
            processed = true;
            return processed;
        }
    return processed;
}

void extracted_orientation(Eigen::Vector3d current_position) {
    std::string x, y, z, ax, ay, az;
    std::ifstream my_csv_file("/home/ghanim/git/baxter_workspace.csv");
    start_index.push_back(extracted_orientations.size());
    while (std::getline(my_csv_file,x,',')) {
        std::getline(my_csv_file, y, ',') ;
        std::getline(my_csv_file, z, ',') ;
        std::getline(my_csv_file, ax, ',') ;
        std::getline(my_csv_file, ay, ',') ;
        std::getline(my_csv_file, az, my_csv_file.widen('\n'));
        Eigen::Vector3d current_point, current_orientation;
        current_point << std::stod(x), std::stod(y), std::stod(z);
        if(current_point == current_position) {
            current_orientation << std::stod(ax), std::stod(ay), std::stod(az);
            extracted_orientations.push_back(current_orientation);
        }
    }
    processed_points.push_back(current_position);
    finish_index.push_back(extracted_orientations.size());
}

int main(int argc, char **argv)
{
    std::ifstream my_csv_file("/home/ghanim/git/baxter_workspace.csv");
    int iteration = 32, counter = 0;
    std::string x, y, z, ax, ay, az;

    while (std::getline(my_csv_file,x,',') && counter < iteration) {
        std::cout << "doing iteration no: " << counter << std::endl;
        std::getline(my_csv_file, y, ',') ;
        std::getline(my_csv_file, z, ',') ;
        std::getline(my_csv_file, ax, ',') ;
        std::getline(my_csv_file, ay, ',') ;
        std::getline(my_csv_file, az, my_csv_file.widen('\n'));
        Eigen::Vector3d current_point;

        current_point << std::stod(x), std::stod(y), std::stod(z);
        std::cout << "dealing with point: " << std::endl << current_point << std::endl;
        if(!processed_point(current_point)) {
            extracted_orientation(current_point);
        }
        counter = counter + 1;
    }
    std::cout << "size of start index is: " << start_index.size() << std::endl ;
    std::cout << "size of finish index is: " << finish_index.size() << std::endl ;
    std::cout << "size of processed points is: " << processed_points.size() << std::endl ;
    std::cout << "size of extracted orientations is: " << extracted_orientations.size() << std::endl ;
    for(int i = 0; i < start_index.size(); i++) {
        std::cout << "orientations associated with point: " << std::endl << processed_points[i] << std::endl << " is: " << std::endl;
        for(int j = start_index[i]; j < finish_index[i]; j++)
            std::cout << "orientation no: " << j << std::endl << extracted_orientations[j] << std::endl ;
    }
}
