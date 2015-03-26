/**
 * @file        SoundManager.cpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#include "SoundManager.hpp"

using namespace Mario;

SoundManager::SoundManager(GameManager* owner) : owner(owner), voice(nullptr), mixer(nullptr)
{
    // register samples
    files[SOUND_MAIN_MENU]  = ASSETS "main.xm";
    files[SOUND_LEVEL_1]    = ASSETS "level1.it";

    LoadSamples();

    voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);

    for (SoundFileSampleList::iterator i = samples.begin(); i != samples.end(); ++i)
        al_attach_audio_stream_to_mixer(i->second, mixer);

    al_attach_mixer_to_voice(mixer, voice);
    al_set_voice_playing(voice, true);
}

SoundManager::~SoundManager()
{
    for (SoundFileSampleList::iterator i = samples.begin(); i != samples.end(); ++i)
        al_destroy_audio_stream(i->second);

    al_destroy_mixer(mixer);
    al_destroy_voice(voice);
}

void SoundManager::LoadSamples()
{
    for (SoundFileList::iterator i = files.begin(); i != files.end(); ++i)
        if (!(samples[i->first] = al_load_audio_stream(i->second.c_str(), 10, 1024)))
            throw std::runtime_error(std::string("Could not load sample ") + i->second);
}

void SoundManager::Stop()
{
    for (SoundFileSampleList::iterator i = samples.begin(); i != samples.end(); ++i)
        al_set_audio_stream_playing(i->second, false);
}

bool SoundManager::Play(SoundFileId sample)
{
    Stop();

    return al_set_audio_stream_playing(samples[sample], true);
}
