#include "core/audio/music_player.hpp"

MusicPlayer::MusicPlayer() : _music{}, _loaded(false) {}

MusicPlayer::~MusicPlayer() { unload(); }

bool MusicPlayer::load(const char *filePath)
{
    unload();
    if (!FileExists(filePath))
    {
        TraceLog(LOG_WARNING, "MusicPlayer: arquivo nao encontrado: %s", filePath);
        return false;
    }
    _music = LoadMusicStream(filePath);
    _loaded = IsMusicValid(_music);
    if (_loaded) _music.looping = true;
    return _loaded;
}

void MusicPlayer::play()  { if (_loaded) PlayMusicStream(_music); }
void MusicPlayer::stop()  { if (_loaded) StopMusicStream(_music); }
void MusicPlayer::update(){ if (_loaded) UpdateMusicStream(_music); }
void MusicPlayer::setVolume(float v) { if (_loaded) SetMusicVolume(_music, v); }

void MusicPlayer::unload()
{
    if (_loaded)
    {
        UnloadMusicStream(_music);
        _music = {};
        _loaded = false;
    }
}