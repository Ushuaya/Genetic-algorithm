//
//  Gameloop_abstract.hpp
//  Live_game
//
//  Created by VolkSeriy on 19.12.2022.
//

#ifndef Gameloop_abstract_hpp
#define Gameloop_abstract_hpp

#include <cstdio>
#include <vector>


class LiveGame_abstract{
    int cellDestiny(int i, int j) = 0;
    void nextStep() = 0;
    std::vector< int > visualize(int iter) = 0;
    std::vector< int > circle(int iter); = 0;
    int get_goodness () = 0;
    std::vector< int > get_prev_step() = 0;
};


#endif /* Gameloop_abstract_hpp */
