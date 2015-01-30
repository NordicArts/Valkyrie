#ifndef NordicArts_Valkyrie_GameStart_H
#define NordicArts_Valkyrie_GameStart_H

#include <Valkyrie/Valkyrie.hpp>

#include <NordicEngine/Window/Layer.hpp>
#include <NordicEngine/Logger/Logger.hpp>

namespace NordicArts {
    namespace Game {
        class GameStart {
        // Variables
        public:
        protected:
        private:
            NordicEngine::Window::Layer *m_pWindowManager;
            NordicEngine::Logger *m_pLogger;

        // Methods
        public:
            GameStart();
            GameStart(NordicEngine::Logger *pLogger);
            
            ~GameStart();

            int startGame();

            NordicEngine::Window::Layer *getWindowManager();

            void setWindowManager(NordicEngine::Window::Layer *pLayer);
            void initalize();
            void gameLoop();
            void destroy();

        protected:
        private:
        
        };
    };
};

#endif
