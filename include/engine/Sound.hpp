#ifndef			__HPP__Sound__
#define			__HPP__Sound__

class Sound {
    public:
        Sound();
        ~Sound();
        void playBGMusic(const char* filename);
        void setVolume(int volume);
    private:
};

#endif