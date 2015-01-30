#ifndef NordicArts_Valkyrie_Main_H
#define NordicArts_Valkyrie_Main_H

#include <Game/Includes.hpp>

namespace NordicArts {
    namespace Game {
        void handleException(std::exception_ptr oException);

        int Main();
    };
};

#endif
