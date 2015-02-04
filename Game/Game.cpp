#include <Game/Game.hpp>
#include <Game/GameStart/GameStart.hpp>

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Logger/Logger.hpp>
#include <NordicEngine/Window/Window.hpp>
#include <NordicEngine/Settings/Settings.hpp>

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

        int Main(std::string cGameName) {
            NordicEngine::Logger  oLogger(cGameName);
            NordicEngine::Logger *pLogger = &oLogger;

            try {   
                NordicEngine::Settings  oSettings(pLogger, cGameName);
                NordicEngine::Settings *pSettings = &oSettings;
                pSettings->setup();
                pSettings->setOpenGLVerbose(4, 1);

                NordicEngine::WindowMaker::Window  oWindow(pLogger, pSettings);
                NordicEngine::WindowMaker::Window *pWindow = &oWindow;

                GameStart oGame(pSettings, pLogger);
                oGame.setWindowManager(pWindow);

                return oGame.startGame();
            } catch (std::exception &oException) {
                throw NordicEngine::Exception(oException.what());
            } catch (NordicEngine::Exception &oException) {
                pLogger->log(oException.what());
            } catch ( ... ) {
                handleException(std::current_exception());
            }

            return EXIT_SUCCESS;
        }
    };
};
