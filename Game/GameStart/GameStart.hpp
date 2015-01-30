#ifndef NordicArts_Valkyrie_GameStart_H
#define NordicArts_Valkyrie_GameStart_H

#include <Game/Game.hpp>

#include <NordicEngine/Window/Window.hpp>
#include <NordicEngine/Logger/Logger.hpp>

namespace NordicArts {
    namespace Game {
        class GameStart {
        // Variables
        public:
        protected:
        private:
            NordicEngine::WindowMaker::Window *m_pWindowManager;
            NordicEngine::Logger *m_pLogger;

        // Methods
        public:
            GameStart();
            GameStart(NordicEngine::Logger *pLogger);
            
            ~GameStart();

            int startGame();

            NordicEngine::WindowMaker::Window *getWindowManager();

            void setWindowManager(NordicEngine::WindowMaker::Window *pLayer);
            void initalize();
            void gameLoop();
            void destroy();

        protected:
        private:
        
        };
    };
};

#endif
