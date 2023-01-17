//
//  Operations.hpp
//  Live_game
//
//  Created by VolkSeriy on 19.12.2022.
//

#ifndef Operations_hpp
#define Operations_hpp

#include <cstdio>
#include <vector>
#include <tuple>
#include <map>
#include <climits>

#include "Play_circle.hpp"
#include "Operations_abstract.hpp"



class GeneticsOP : public GeneticsOP_abstract{
private:
    using Mtr_type = std::vector<int> ;
    std::vector<Mtr_type> Population;
    std::vector<int> spicies_good_prev;
    std::vector<int> spicies_good;
    uint iteration_quantity = 50;
    uint Population_quantity;
    double probability_crossbreed = 0.8;
    uint Mtr_size = 50;
    long double mutation_prob = 0.0004;
    
    std::vector <std::vector  <long double>> Mutate_population;
    std::map <int, int> Mutate_population_coords;
public:
    Mtr_type best_solution;
    uint best_solution_val = UINT_MAX;

    
    GeneticsOP(int population_quantity_out, int N, long double mutation_prob_out = 0.0004, uint iteration_quantity_out = 50){
        iteration_quantity = iteration_quantity_out;
        Mtr_size = N;
        Population_quantity = population_quantity_out;
        Mtr_type Matrix(N*N);
        for (int i = 0; i < Population_quantity; i++){
            std::generate(Matrix.begin(), Matrix.end(), [](){return std::rand()%2;});
            Population.push_back(Matrix);
        }
        mutation_prob = mutation_prob_out;
        
        for (int i = 0; i < population_quantity_out; i++){
            std::vector <long double> v(N*N, mutation_prob_out) ;
            Mutate_population.push_back(v);
        }
    }
    
    Mtr_type get_best_solution(){
        return best_solution;
    }
    
    uint get_best_solution_val(){
        return best_solution_val;
    }
    
    
    static int calc_goodness(std::vector< int > Mtr_out, int iterations, uint matr_size_out){
        auto loop = LiveGame(Mtr_out, matr_size_out);
        auto result = loop.circle(iterations);
        return loop.get_goodness();
    }
    
    void population_value(){
        spicies_good_prev = spicies_good;
        spicies_good.clear();
        for (auto &i: Population){
            auto loop = LiveGame(i, Mtr_size);
            auto result = loop.circle(iteration_quantity);
            if (loop.get_prev_step() != result){
                auto GOODDD = loop.get_goodness();
                if (GOODDD < best_solution_val && GOODDD != 0){
                    best_solution = i;
                    best_solution_val = GOODDD;
                }
                
                spicies_good.push_back(GOODDD);
            }
            else{
                spicies_good.push_back(0);
            }
        }
    }
    
    void kill_spicies(){
        
        while(Population.size() != Population_quantity){
            uint summ_good = [this](){uint summ_tmp = 0; for (auto &i: spicies_good){ summ_tmp += i;} return summ_tmp; }();
            long double average_summ = summ_good/spicies_good.size();
            auto tmp_1 = Population.size();
            for (int i = 0; i < Population.size(); i++){
                if ((double) spicies_good[i] / summ_good < ((double) rand() / (RAND_MAX))){
                    spicies_good.erase(spicies_good.begin() + i, spicies_good.begin() + i + 1);
                    Population.erase(Population.begin() + i, Population.begin() + i + 1);
                    Mutate_population.erase(Mutate_population.begin() + i, Mutate_population.begin() + i + 1);
                    i++;
                }
                if (Population.size() == Population_quantity)
                    break;
            }
            auto tmp_2 = Population.size();
            if (tmp_1 == tmp_2){
                uint tmp_rand_pos = rand() % Population.size();
                spicies_good.erase(spicies_good.begin() + tmp_rand_pos, spicies_good.begin() + tmp_rand_pos + 1);
                Population.erase(Population.begin() + tmp_rand_pos, Population.begin() + tmp_rand_pos + 1);
                Mutate_population.erase(Mutate_population.begin() + tmp_rand_pos, Mutate_population.begin() + tmp_rand_pos + 1);
            }
            //uint tmp_rand_pos = rand() % Population.size();
            
//            if ((double) spicies_good[tmp_rand_pos] / average_summ < ((double) rand() / (RAND_MAX))){
//                spicies_good.erase(spicies_good.begin() + tmp_rand_pos, spicies_good.begin() + tmp_rand_pos + 1);
//                Population.erase(Population.begin() + tmp_rand_pos, Population.begin() + tmp_rand_pos + 1);
//            }
        }
    }
        
    template<typename T>
    std::vector<T> slice(std::vector<T> const &v, int m, int n)
    {
        auto first = v.cbegin() + m;
        auto last = v.cbegin() + n;
     
        std::vector<T> vec(first, last);
        return vec;
    }
    
    void make_new_spicies(uint coord_out){
        
        // Two point crossbreed
        auto all_Mtr_size = Mtr_size * Mtr_size;
        uint sequent_1 = (rand() + 1) % (all_Mtr_size - 1);
        uint sequent_2 = (rand() + 1) % (all_Mtr_size - 1);
        while (sequent_1 == sequent_2){
            sequent_1 = (rand() + 1) % (all_Mtr_size - 1);
            sequent_2 = (rand() + 1) % (all_Mtr_size - 1);
        }
        
        if (sequent_2 < sequent_1)
            std::swap(sequent_1, sequent_2);
        
        uint sequent_3 = (rand() + 1) % (all_Mtr_size - 1);
        while (sequent_3 + sequent_2 - sequent_1 > all_Mtr_size){
            sequent_3 = (rand() + 1) % (all_Mtr_size - 1);
        }
        uint sequent_4 = sequent_3 + sequent_2 - sequent_1;
        
        auto coord = rand() % Population.size();
        auto coord_2 = rand() % Population.size();
        
        while (coord_2 == coord)
            coord_2 = rand() % Population.size();
        
        Mtr_type left_part_1 = slice(Population[coord], 0, sequent_1);
        Mtr_type right_part_1 = slice(Population[coord], sequent_2, all_Mtr_size);
        Mtr_type Middle_part_2 = slice(Population[coord_2], sequent_1, sequent_2);
        left_part_1.insert(left_part_1.end(), Middle_part_2.begin(), Middle_part_2.end() );
        left_part_1.insert(left_part_1.end(), right_part_1.begin(), right_part_1.end() );
        Population.push_back(left_part_1);
        Mutate_population.push_back(std::vector <long double> (all_Mtr_size, mutation_prob));
        
        Mtr_type left_part_2 = slice(Population[coord_2], 0, sequent_3);
        Mtr_type right_part_2 = slice(Population[coord_2], sequent_4, all_Mtr_size);
        Mtr_type Middle_part_1 = slice(Population[coord], sequent_3, sequent_4);
        left_part_2.insert(left_part_2.end(), Middle_part_1.begin(), Middle_part_1.end() );
        left_part_2.insert(left_part_2.end(), right_part_2.begin(), right_part_2.end() );
        Population.push_back(left_part_2);
        Mutate_population.push_back(std::vector <long double> (all_Mtr_size, mutation_prob));
        
    }
    
    void crossbreeed(){
        uint tmp = Population.size();
        for (uint i = 0; i < tmp-1; i++){
            if ((double) rand()/RAND_MAX < 0.8)
                make_new_spicies(i);
        }
    }
    
    void mutate(){
        uint tmp = Population.size();
        for (int i = 0; i < Mutate_population.size(); i++){
            for (int j = 0; j < Mutate_population[i].size(); j++){
                if (((double) rand() / RAND_MAX) < Mutate_population[i][j]){
                    Population[i][j] = !Population[i][j];
                    Mutate_population_coords[i] = j;
                }
            }
        }
    }
    
    void change_mutation_matrix(){
        //uint tmp = Population.size();
        for (int i = 0; i < spicies_good.size(); i++){
            if (spicies_good[i] < spicies_good_prev[i]){
                Mutate_population[i][Mutate_population_coords[i]] += mutation_prob;
            }
            else{
                if (Mutate_population[i][Mutate_population_coords[i]] > 0.1)
                    Mutate_population[i][Mutate_population_coords[i]] -= mutation_prob;
            }
        }
    }
    
};

#endif /* Operations_hpp */
