#include <Game/Game.hpp>
#include <Game/GameStart/GameStart.hpp>

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Logger/Logger.hpp>
#include <NordicEngine/Window/Layer.hpp>

namespace NordicArts {
    namespace Game {
        void handleException(std::exception_ptr oException) {
            try {
                if (oException) {
                    std::rethrow_exception(oException);
                }
            } catch ( const std::exception &oEx) {
                printIt(oEx.what());
            }
        }

        int Main(std:string cGameName) {
            try {   
                NordicEngine::Logger  oLogger(cGameName);
                NordicEngine::Logger *pLogger = &oLogger;

                NordicEngine::Window::Layer  oWindow(pLogger);
                NordicEngine::Window::Layer *pWindow = &oWindow;

                GameStart oGame(pLogger);
                oGame.setWindowManager(pWindow);

                return oGame.startGame();
            } catch (std::exception &oException) {
                throw NordicEngine::Exception(oException.what());
            } catch (NordicEngine::Exception &oException) {
                printIt(oException.what());
            } catch ( ... ) {
                handleException(std::current_exception());
            }

            return EXIT_SUCCESS;
        }
    };
};
