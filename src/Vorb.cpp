#include "stdafx.h"
#include "Vorb.h"

#include <boost/filesystem.hpp>

#include "graphics/ConnectedTextures.h"
#include "io/IOManager.h"
#include "sound/SoundEngine.h"
#include "utils.h"

namespace vorb {
    // Current system settings
    InitParam currentSettings = InitParam::NONE;
    bool isSystemInitialized(const InitParam& p) {
        return (currentSettings & p) != InitParam::NONE;
    }

    /************************************************************************/
    /* Initializers                                                         */
    /************************************************************************/
    InitParam initGraphics() {
        // Check for previous initialization
        if (isSystemInitialized(InitParam::GRAPHICS)) {
            return InitParam::GRAPHICS;
        }

        vg::ConnectedTextureHelper::init();
        return InitParam::GRAPHICS;
    }
    InitParam initIO() {
        // Check for previous initialization
        if (isSystemInitialized(InitParam::IO)) {
            return InitParam::IO;
        }

        // Correctly retrieve initial path
        vpath path = boost::filesystem::initial_path().string();

        // Set the executable directory
#ifdef OS_WINDOWS
        {
            nString buf(1024, 0);
            GetModuleFileName(nullptr, &buf[0], 1024 * sizeof(TCHAR));
            path = buf;
            path--;
        }
#else
        // TODO: Investigate options

#endif // OS_WINDOWS
        if (!path.isValid()) path = "."; // No other option
        vio::IOManager::setExecutableDirectory(path.asCanonical());

        // Set the current working directory
        path = boost::filesystem::current_path().string();
        if (!path.isValid()) path = "."; // No other option
        if (path.isValid()) vio::IOManager::setCurrentWorkingDirectory(path.asCanonical());

#ifdef DEBUG
        printf("Executable Directory:\n    %s\n", vio::IOManager::getExecutableDirectory().getCString());
        printf("Current Working Directory:\n    %s\n\n\n", !vio::IOManager::getCurrentWorkingDirectory().isNull()
            ? vio::IOManager::getCurrentWorkingDirectory().getCString()
            : "None Specified");
#endif // DEBUG

        return InitParam::IO;
    }
    InitParam initSound() {
        // Check for previous initialization
        if (isSystemInitialized(InitParam::SOUND)) {
            return InitParam::SOUND;
        }

        if (!vsound::impl::initSystem()) return InitParam::NONE;

        return InitParam::SOUND;
    }
    
    /************************************************************************/
    /* Disposers                                                            */
    /************************************************************************/
    InitParam disposeGraphics() {
        // Check for existence
        if (!isSystemInitialized(InitParam::GRAPHICS)) {
            return InitParam::GRAPHICS;
        }

        return InitParam::GRAPHICS;
    }
    InitParam disposeIO() {
        // Check for existence
        if (!isSystemInitialized(InitParam::IO)) {
            return InitParam::IO;
        }

        return InitParam::IO;
    }
    InitParam disposeSound() {
        // Check for existence
        if (!isSystemInitialized(InitParam::SOUND)) {
            return InitParam::SOUND;
        }
        
        if (!vsound::impl::disposeSystem()) return InitParam::NONE;

        return InitParam::SOUND;
    }
}

vorb::InitParam vorb::init(const InitParam& p) {
#define HAS(v, b) ((v & b) != InitParam::NONE)

    vorb::InitParam succeeded = InitParam::NONE;
    if (HAS(p, InitParam::SOUND)) succeeded |= initSound();
    if (HAS(p, InitParam::GRAPHICS)) succeeded |= initGraphics();
    if (HAS(p, InitParam::IO)) succeeded |= initIO();

    // Add system flags
    currentSettings |= succeeded;

    return succeeded;

#undef HAS
}
vorb::InitParam vorb::dispose(const InitParam& p) {
#define HAS(v, b) ((v & b) != InitParam::NONE)

    vorb::InitParam succeeded = InitParam::NONE;
    if (HAS(p, InitParam::SOUND)) succeeded |= disposeSound();
    if (HAS(p, InitParam::GRAPHICS)) succeeded |= disposeGraphics();
    if (HAS(p, InitParam::IO)) succeeded |= disposeIO();

    // Remove system flags
    currentSettings &= (InitParam)(~(ui64)succeeded);

    return succeeded;

#undef HAS
}