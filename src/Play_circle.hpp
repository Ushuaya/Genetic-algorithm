//
//  Play_circle.hpp
//  Live_game
//
//  Created by VolkSeriy on 05.12.2022.
//

#ifndef Play_circle_hpp
#define Play_circle_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>





class LiveGame{
private:
    std::vector< int > Mtr_prev_step;
    std::vector< int > Mtr;
    int N;
    int goodness = 0;
public:
    LiveGame(std::vector< int > Mtr_out, uint N_out): Mtr(Mtr_out), N(N_out){}
    
    void showMatrix(){
        int i,j;
        std::string tmp_cout = "";
        for(i = 0; i<N; i++){
            for(j = 0; j<N; j++)
                if(Mtr[i*N + j])
                    tmp_cout += "■";
                else
                    tmp_cout += "□";
            tmp_cout += "\n";
        }
        tmp_cout += "\n";
        std::cout << tmp_cout;
    }
    
    static std::string showMatrix(std::vector< int > M, int N){
        int i,j;
        std::string tmp_cout = "";
        for(i = 0; i<N; i++)
        {   for(j = 0; j<N; j++)
                if(M[i*N + j])
                    tmp_cout += "Х";
                else
                    tmp_cout += "-";
            tmp_cout += "\n";
        }
        tmp_cout += "\n";
        return tmp_cout;
    }
    

     
    int cellDestiny(int i, int j){
        int neighbors = -Mtr[i*N + j];
        int k = i-1, m = j - 1, k_max = i + 1, m_max = j + 1;
        if (i == 0){
            k = i;
        }
        if (i == N-1){
            k_max = i;
        }
        if (j == 0){
            m = j;
        }
        if (j == N-1){
            m_max = j;
        }
        for(int iter_k = k; iter_k <= k_max; iter_k++)
            for(int iter_m = m; iter_m <= m_max; iter_m++)
                neighbors += Mtr[iter_k*N + iter_m];
        
     
        if(neighbors == 3 || (neighbors == 2 && Mtr[i*N + j]))
            return 1;
     
        return 0;
    }
     
    void nextStep(){
        std::vector< int > tmp(N*N, 0);
        int count_gogness = 0;
        for(int i = 0; i<N; i++)
            for(int j = 0; j<N; j++){
                auto tmp_val = cellDestiny(i, j);
                if (tmp_val){
                    count_gogness += 1;
                }
                tmp[i*N + j]  = tmp_val;
            }
        Mtr_prev_step = Mtr;
        Mtr = tmp;
    }
    
    std::vector< int > visualize(int iter)
    {
        showMatrix();
        for (int i = 0; i < iter; i++){
            nextStep();
            std::cout << "\x1B[2J\x1B[H" << std::flush;
            showMatrix();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        return Mtr;
    }
    
    std::vector< int > circle(int iter){
        for (int i = 0; i < iter; i++){
            nextStep();
        }
        return Mtr;
    }
    
    int get_goodness (){
        uint count_gogness = 0;
        for(int i = 0; i<N; i++)
            for(int j = 0; j<N; j++)
                if (Mtr[i*N + j])
                    count_gogness += 1;
        return count_gogness;
    }
    
    std::vector< int > get_prev_step(){
        return Mtr_prev_step;
    }
};

#endif /* Play_circle_hpp */
