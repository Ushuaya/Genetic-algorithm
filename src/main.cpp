//
//  main.cpp
//  Live_game
//
//  Created by VolkSeriy on 05.12.2022.
//
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <fstream>

#include "Play_circle.hpp"
#include "Genetics.hpp"
#define N 50
#define POPULATION 50
#define Iterations 100


 

 
int main()

{
    

    
    srand((unsigned int) time(NULL));
//    std::srand(unsigned(std::time(nullptr)));
//    std::vector<std::vector<int> > Matrix(N, std::vector<int>(N));
//    for (auto &i:  Matrix){
//        std::generate(i.begin(), i.end(), [](){return std::rand()%2;});
//    }
//
//
////    std::vector<std::vector<int> > Matrix(N, std::vector<int>(N, 0));
////    Matrix[0][0] = 1;
////    Matrix[0][1] = 1;
////    Matrix[1][0] = 1;
////    Matrix[1][1] = 1;
//
//
//    auto loop = LiveGame(Matrix);
//    auto result = loop.visualize(200);
//    loop.showMatrix();
//
//    int **M = (int**) malloc(N*sizeof(int*));
//    for(i = 0; i<N; i++)
//        M[i] = (int*) malloc(N*sizeof(int));
    
    std::ofstream ofile;
    ofile.open("res_end.txt", std::ios::app);
    ofile << std::endl << "NEW RESEARCH" << std::endl ;
     //app is append which means it will put the text at the end
    //ofile << i << " " << x << " " << y << std::endl;

    long double Mutate_prob = 0.0004;
    for (int i = 0; i < 10; i++){
        auto Mutate_prob_next = Mutate_prob * pow(1.5, i);
        std::cout << Mutate_prob_next << std::endl;
        ofile << std::endl << "NEW MUTATE_PROB: " << std::to_string(Mutate_prob_next) << std::endl ;

        for (int j = 0; j < 10; j++){
            std::cout << i << " " << j << std::endl;
            auto start = std::chrono::system_clock::now();
            auto DeGenerat = Genetics();
            auto res = DeGenerat.main_cycle(POPULATION, N, Mutate_prob, Iterations);
            auto res_num = GeneticsOP::calc_goodness(res, Iterations, N);
            ofile << "VALUE: " << res_num << std::endl ;
            auto end = std::chrono::system_clock::now();
            auto duration = duration_cast<std::chrono::seconds>(end - start);
            ofile << "\tTIME: " << (duration).count() << std::endl;

            std::ofstream vis_result;
            vis_result.open("series_" + std::to_string(i) + "_run_" + std::to_string(j) + ".txt");
            vis_result << LiveGame::showMatrix(res, N);
            vis_result << std::endl;
            vis_result << LiveGame::showMatrix(std::move(LiveGame(res, N).circle(Iterations)), N);


        }



    }

    ofile.close();

    
    
//
//    long double Mutate_prob = 0.0004;
//    auto DeGenerat = Genetics();
//    auto res = DeGenerat.main_cycle(POPULATION, N, Mutate_prob, Iterations);
//    auto loop = LiveGame(res, N);
//    loop.visualize(Iterations);
//
//
//
    
 
    return 0;
}
