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
            this->initalize();
            this->gameLoop();
            this->destroy();

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

            m_pModelManager->addModel("triangle", "GameFiles/Models/triangle.obj", "GameFiles/Shaders/Shader.vertex", "GameFiles/Shaders/Shader.fragment");
            m_pModelManager->addModel("dragon", "GameFiles/Models/dragon.obj", "GameFiles/Shaders/Shader.vertex", "GameFiles/Shaders/Shader.fragment");
        }

        void GameStart::gameLoop() {
            if (m_pWindowManager) {
                NordicEngine::Render::Models::Model *pTriangle = m_pModelManager->getModel("triangle");
                std::cout << "Triangle: " << pTriangle << std::endl;

                pTriangle = NULL;
                std::cout << "Triangle: " << pTriangle << std::endl;

                if (pTriangle != nullptr) { pTriangle->initalize(); }
                std::cout << "Triangle: " << pTriangle << std::endl;

                NordicEngine::Render::Models::Model *pDragon = m_pModelManager->getModel("dragon");
                if (pDragon != nullptr) { pDragon->initalize(); }
                std::cout << "Stuffs .. " << pDragon << std::endl;

                std::cout << "Models..." << m_pModelManager->m_iModels << std::endl;

                m_pLogger->log(pDragon->getStats());

                while (m_pWindowManager->processInput(true)) {
                    m_pRender->clear();

                    if (pTriangle != nullptr) { pTriangle->render(); }
                    if (pDragon != nullptr) { pDragon->render(); }

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
