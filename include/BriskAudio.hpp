#pragma once

#include <string>

namespace BriskAudio {
enum class Exit {
    SUCCESS,
    FAILURE
};

enum class DeviceType {
    PLAYBACK,
    CAPTURE
};

enum class BufferFormat {
    U_INT_8,
    S_INT_16,
    S_INT_24,
    S_INT_32,
    FLOAT_32,
    FLOAT_64
};

struct Stream {
private:
    BufferFormat format_;
    unsigned int numChannels_;
    unsigned int sampleRate_;
};

struct Device {
    std::string name;
    DeviceType type;
    void* nativeHandle;

    Device()
    {
        name = "??????";
        type = DeviceType::PLAYBACK;
        nativeHandle = nullptr;
    }

    ~Device();

    bool isStreamFormatSupported(BufferFormat aFormat, unsigned int aNumChannels, unsigned int aSampleRate);
    Exit openStream(Stream& arStream, BufferFormat aFormat, unsigned int aNumChannels, unsigned int aSampleRate);
    Exit closeStream(Stream& arStream);
};

struct DeviceEventNotifier;

Exit init();
Exit getDeviceCount(unsigned int& arDeviceCount, DeviceType aType);
Exit openDefaultDevice(Device& arDevice, DeviceType aType);
Exit openDevice(Device& arDevice, unsigned int aIndex, DeviceType aType);
Exit openDevice(Device& arDevice, std::string aDeviceName);
Exit closeDevice(Device& arDevice);
Exit quit();
}
