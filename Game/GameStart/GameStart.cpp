#include <Game/GameStart/GameStart.hpp>

#include <NordicEngine/Render/Models/Model.hpp>
#include <NordicEngine/Color/Color.hpp>

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

            // Render
            NordicEngine::Render::Manager oRender(m_pLogger);
            m_pRender = &oRender;

            // Hide the cursor
            m_pWindowManager->setCursorDisabled();

            // Clear Color
            m_pRender->clearColor(NordicEngine::Color::Blue);

            // Set Depth tests
            m_pRender->depthAndCull();

            NordicEngine::Render::Models::Manager oManager(m_pLogger);
            m_pModelManager = &oManager;

            std::vector<glm::vec3> vVerticies;
            
            glm::vec3 vVert;
            vVert.x = -1.0f;
            vVert.y = -1.0f;
            vVert.z =  0.0f;
            vVerticies.push_back(vVert);
        
            vVert.x =  1.0f;
            vVert.y = -1.0f;
            vVert.z =  0.0f;
            vVerticies.push_back(vVert);
    
            vVert.x = 0.0f;
            vVert.y = 1.0f;
            vVert.z = 0.0f;
            vVerticies.push_back(vVert);

            m_pModelManager->addModel("triangle", vVerticies, "GameFiles/Shaders/Shader.vertex", "GameFiles/Shaders/Shader.fragment");
        }

        void GameStart::gameLoop() {
            if (m_pWindowManager) {
                NordicEngine::Render::Models::Model *pTriangle = m_pModelManager->getModel("triangle");
                pTriangle->initalize();

                while (m_pWindowManager->processInput(true)) {
                    m_pRender->clear();

                    pTriangle->render();
                    //m_pModelManager->renderAll();

                    m_pWindowManager->swapBuffers();
                }
            }
        }

        void GameStart::destroy() {
            m_pRender->destroy();
            m_pWindowManager->destroy();
        }
    };
};
