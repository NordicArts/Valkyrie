#include <Game/GameStart/GameStart.hpp>

#include <NordicEngine/Render/Models/Model.hpp>
#include <NordicEngine/Render/Models/Manager.hpp>
#include <NordicEngine/ThirdParty/glm/glm/glm.hpp>

namespace NordicArts {
    namespace Game {
        NordicEngine::Render::Models::Model g_Triangle;

        GameStart::GameStart() {
        }
        GameStart::GameStart(NordicEngine::Logger *pLogger) : m_pLogger(pLogger) {
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

        int GameStart::startGame() {
            initalize();
            gameLoop();
            destroy();
            
            return 0;
        }

        void GameStart::initalize() {
            if (!m_pWindowManager || (m_pWindowManager->initalize(1024, 768, "Valkyrie", false) != 0)) {
                exit(-1);
            }

            NordicEngine::Render::Models::Manager oManager;

            g_Triangle = oManager.addModel("triangle", "GameFiles/Models/Triangle.obj", "GameFiles/Shaders/Shader.vertex", "GameFiles/Shaders/Shader.fragment");
        }

        void GameStart::gameLoop() {
            while (m_pWindowManager->processInput(true)) {
                glClear(GL_COLOR_BUFFER_BIT);

                g_Triangle.render();

                m_pWindowManager->swapBuffers();
            }
        }

        void GameStart::destroy() {
            g_Triangle.destroy();

            if (m_pWindowManager) {
                m_pWindowManager->destroy();

                SAFE_DELETE(m_pWindowManager);
            }

            if (m_pLogger) {
                SAFE_DELETE(m_pLogger);
            }
        }
    };
};
