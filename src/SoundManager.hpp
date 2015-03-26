/**
 * @file        SoundManager.hpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#ifndef __SoundManager__
#define __SoundManager__

#include "Common.hpp"
#include "GameManager.hpp"

namespace Mario
{
    typedef std::map<SoundFileId, std::string> SoundFileList;
    typedef std::map<SoundFileId, ALLEGRO_AUDIO_STREAM*> SoundFileSampleList;

    struct SoundManager
    {
        SoundManager(GameManager* owner);
        ~SoundManager();

        void LoadSamples();
        void Stop();
        bool Play(SoundFileId sample);

        SoundFileList files;
        SoundFileSampleList samples;
        GameManager* owner;
        ALLEGRO_VOICE* voice;
        ALLEGRO_MIXER* mixer;
    };
}

#endif
