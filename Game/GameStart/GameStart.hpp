#ifndef NordicArts_Valkyrie_GameStart_H
#define NordicArts_Valkyrie_GameStart_H

#include <Game/Game.hpp>

#include <NordicEngine/Window/Window.hpp>
#include <NordicEngine/Logger/Logger.hpp>
#include <NordicEngine/Render/Models/Manager.hpp>
#include <NordicEngine/Settings/Settings.hpp>
#include <NordicEngine/Render/Manager.hpp>

namespace NordicArts {
    namespace Game {
        class GameStart {
        // Variables
        public:
        protected:
        private:
            NordicEngine::Render::Models::Manager   *m_pModelManager;
            NordicEngine::WindowMaker::Window       *m_pWindowManager;
            NordicEngine::Logger                    *m_pLogger;
            NordicEngine::Settings                  *m_pSettings;
            NordicEngine::Render::Manager            *m_pRender;

        // Methods
        public:
            GameStart();
            GameStart(NordicEngine::Settings *pSettings, NordicEngine::Logger *pLogger);
            
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
