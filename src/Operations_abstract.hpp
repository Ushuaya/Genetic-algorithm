//
//  Operations_abstract.hpp
//  Live_game
//
//  Created by VolkSeriy on 19.12.2022.
//

#ifndef Operations_abstract_hpp
#define Operations_abstract_hpp

#include <stdio.h>
#include <vector>
#include <tuple>
#include <map>
#include <climits>

#include "Play_circle.hpp"

class GeneticsOP_abstract{
private:
    using Mtr_type = std::vector<int> ;
public:
//    virtual Mtr_type best_solution = 0;
//    virtual uint best_solution_val = 0;
    virtual Mtr_type get_best_solution() = 0;
    
    virtual uint get_best_solution_val() = 0;
    
    virtual void population_value() = 0;
    
    virtual void kill_spicies() = 0;
        
    virtual void make_new_spicies(uint coord_out) = 0;
    
    virtual void crossbreeed() = 0;
    
    virtual void mutate() = 0;
    
    virtual void change_mutation_matrix() = 0;
    
};

#endif /* Operations_abstract_hpp */
