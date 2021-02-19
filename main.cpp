#include <iostream>
#include <vector>
#include <fstream>
#include <casmutils/definitions.hpp>
#include <casmutils/xtal/structure.hpp>
#include <casmutils/xtal/structure_tools.hpp>
#include <casmutils/xtal/coordinate.hpp>
#include <casmutils/xtal/symmetry.hpp>
#include <casmutils/sym/group-io.hpp>
//#include <casmutils/xtal/lattice.hpp>
//#include <casmutils/xtal/site.hpp>
#include <casmutils/sym/symgroup.hpp>
#include <CLI/CLI.hpp>
//#include "json_conv.hpp"

namespace cu=casmutils;

int main(int argc, char* argv[]){

    /* read in a poscar, find the Factor group, and print to a json;
     * factor group contain a vector of CartOps which
     * Each CartOp contains a Matrix(EigenMatrix3d),
     *                      a translation(Eigen Vector3d), and
     *                      a timereversal (Boolean)
     */


    //First parse the input arguments
    CLI::App app{"This utility reads in a POSCAR Path, determines the factor group and then prints it to a json file in the current directory or at the given output path"};
    cu::fs::path input_poscar_path;
    cu::fs::path output_path;
    double tol=1e-6;

    CLI::Option* inputPath = app.add_option("-s, --structure", input_poscar_path, "Path to input POSCAR file.")->required()->check(CLI::ExistingFile);
    CLI::Option* outputPath = app.add_option("-o, --output", output_path, "Path to output POSCAR file.");

    CLI11_PARSE(app, argc, argv);

    //read the input poscar and store as structure
    cu::xtal::Structure input_structure=cu::xtal::Structure::from_poscar(input_poscar_path);

    //generate factor group
    std::vector<casmutils::sym::CartOp> factor_group=make_factor_group(input_structure, tol);
    
    //convert factor group object into json type
    print_group_to_file(factor_group, output_path);

    //output json group to file
//    std::ofstream ofs(output_path);
//    ofs<<group_json.dump(group_json.size());
//    ofs.close();
//
    return 0;
}
