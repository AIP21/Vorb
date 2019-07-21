//
// Mod.h
// Vorb Engine
//
// Created by Matthew Marshall on 16 July 2019
// Copyright 2019 Regrowth Studios
// MIT License
//

/*! \file Mod.h
 * \brief Holds all things needed for a given mod. This includes the mod's metadata, but also
 * basic utilities such as an IO manager, texture cache etc.
 */

#pragma once

#ifndef Vorb_Mod_h__
//! @cond DOXY_SHOW_HEADER_GUARDS
#define Vorb_Mod_h__
//! @endcond

#ifndef VORB_USING_PCH
#include "../types.h"
#endif // !VORB_USING_PCH

#include "Vorb/mod/ModIOManager.h"
#include "Vorb/io/Keg.h"

namespace vorb {
    namespace mod {
        struct ModMetadata {
            nString name;
            nString author;
            // TODO(Matthew): More metadata info.
        };
        const ModMetadata NULL_METADATA = {
            "", ""
        };

        struct ModEntryPoints {
            Array<nString> blockFiles;
            Array<nString> caFiles;
            Array<nString> musicFiles;
            // TODO(Matthew): Expand as features get implemented, e.g. ecs stuff, creatures, ore gen, etc.
        };

        const nString METADATA_FILENAME     = "mod.yaml";
        const nString ENTRY_POINTS_FILENAME = "entry_points.yaml";
        const nString MANIFEST_FILENAME     = "manifest.yaml";

        class Mod {
        public:
            Mod();
            ~Mod() {
                // Empty.
            }

            /*!
             * \brief Initialises the mod, setting up necessary data, including loading
             * associated metadata.
             *
             * \param dir: The directory name of the mod to be initialised (not the full path, just the name of the directory inside of Mods/).
             *
             * \return True if the mod was correctly initialised, false otherwise.
             */
            virtual bool init(const nString& dir);
            /*!
             * \brief Disposes of the mod.
             */
            virtual void dispose();

            // TODO(Matthew): Determine start up and shut down processes for mods.
            //                    For scripted this will be a bit more obvious, but YAML this may still be TBD.
            /*!
             * \brief Starts up the mod.
             *
             * \return True if successfully started, false otherwise.
             */
            virtual bool startup();
            /*!
             * \brief Shuts down the mod.
             *
             * \return True if successfully shutdown, false otherwise.
             */
            virtual bool shutdown();

            // TODO(Matthew): Once we implement mod timing, we may find a mod is forced to skip frames. We will need to accumulate dt in that case, maybe do other things.
            /*!
             * \brief Run update loop of the mod.
             *
             * \param dt: The time since the last frame.
             */
            virtual void update(f32 dt = 0.0f);

            /*!
             * \brief Generates the mod directory name for the named mod.
             *
             * \param modName: The name of the mod to generate the dir name for.
             *
             * \return The generated mod directory name.
             */
            static nString generateModDirName(const nString& modName);
        protected:
            /*!
             * \brief Loads metadata.
             *
             * The metadata is specified in the file "mod.yaml".
             *
             * \return True if metadata loaded correctly, false otherwise.
             */
            bool loadMetadata();

            ModMetadata  m_metadata;
            // TODO(Matthew): We want to be able to pass our own ModIOManager into the texture and font caches as we only want certain directories to be readable.
            //                    To achieve this, we should make an IOManager interface, and add an optional IOManager pointer to the appropriate cache fetch functions.
            ModIOManager m_iomanager;

            bool m_isStarted;
        };
    }
}
namespace vmod = vorb::mod;

KEG_TYPE_DECL(ModMetadata);
KEG_TYPE_DECL(ModEntryPoints);

#endif // !Vorb_Mod_h__
