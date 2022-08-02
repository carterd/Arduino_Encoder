#ifndef _ENCODER_H_
#define _ENCODER_H_

class Encoder {
    
public:
    enum class EncoderKey {
        ENCODER_LEFT,
        ENCODER_RIGHT,
        ENCODER_ENTER
    };

    bool keyPressed();
    EncoderKey lastKeyPressed();
    virtual void update() = 0;

protected:
    bool mKeyPressed = false;
    EncoderKey mLastKeyPressed = EncoderKey::ENCODER_ENTER;
private:
};

#endif