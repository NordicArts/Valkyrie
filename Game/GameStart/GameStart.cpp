#include <Game/GameStart/GameStart.hpp>

#include <NordicEngine/Render/Models/Model.hpp>
#include <NordicEngine/ThirdParty/glm/glm/glm.hpp>

namespace NordicArts {
    namespace Game {
        GameStart::GameStart() {
        }
        GameStart::GameStart(NordicEngine::Settings *pSettings, NordicEngine::Logger *pLogger) : m_pSettings(pSettings), m_pLogger(pLogger) {
        }

        GameStart::~GameStart() {
            destroy();
        }

        NordicEngine::WindowMaker::Window *GameStart::getWindowManager() {
            return m_pWindowManager;
        }
        
        void GameStart::setWindowManager(NordicEngine::WindowMaker::Window *pManager) {
            m_pWindowManager = pManager;
        }

        // Start the game itself
        int GameStart::startGame() {
            initalize();
            gameLoop();
            destroy();
            
            return 0;
        }

        void GameStart::initalize() {
            if (m_pSettings) {
                if (!m_pWindowManager || (m_pWindowManager->initalize(m_pSettings->getResolutionWidth(), m_pSettings->getResolutionHeight(), m_pSettings->getGameName(), m_pSettings->isWindowed()) != 0)) {
                    return;
                }
            } else {
                if (!m_pWindowManager || (m_pWindowManager->initalize(1024, 768, "Valkyrie", false) != 0)) {
                    return;
                }
            }

            // Hide the cursor
            m_pWindowManager->setCursorDisabled();

            NordicEngine::Render::Models::Manager oManager(m_pLogger);
            m_pModelManager = &oManager;

            m_pModelManager->addModel("triangle", "GameFiles/Models/triangle.obj", "GameFiles/Shaders/Shader.vertex", "GameFiles/Shaders/Shader.fragment");
        }

        void GameStart::gameLoop() {
            if (m_pLogger) { m_pLogger->log("Started Game Loop"); }

            if (m_pWindowManager) {
                if (m_pLogger) { m_pLogger->log("Started GameLoop Render"); }

                NordicEngine::Render::Models::Model *pTriangle = m_pModelManager->getModel("triangle");

                while (m_pWindowManager->processInput(true)) {
                    m_pWindowManager->clearWindow();

                    pTriangle->render();

                    m_pWindowManager->swapBuffers();
                }

                if (m_pLogger) { m_pLogger->log("Ended GameLoop Render"); }
            }

            if (m_pLogger) { m_pLogger->log("Ended Game Loop"); }
        }

        void GameStart::destroy() {
            m_pWindowManager->destroy();
        }
    };
};
