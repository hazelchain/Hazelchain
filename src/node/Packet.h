//
// Created by chris on 2021-08-27.
//

#ifndef HAZELCHAIN_PACKET_H
#define HAZELCHAIN_PACKET_H

#include <vector>
#include <array>
#include <cstddef>
#include <variant>
#include <typeinfo>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>

#define HEADER_SIZE 12
#define PROTOCOL_VERSION 1
#define INT_SIZE 4

enum ServerPacket {
    welcome,
};

enum ClientPacket {
    HANDSHAKE
};

class Packet {
private:
    std::vector<unsigned char> buffer_;
    unsigned int readPos_ = 0;
    int size_ = -1;

public:
    using value_t = std::variant<
            std::string,
            int,
            unsigned int,
            unsigned long,
            unsigned long long int,
            float
    >;
    using values_t = std::vector<value_t>;

    const bool writable_;
    int id;

    explicit Packet(int id);

    explicit Packet(std::vector<char> in);

// region functions

    void SetBytes(unsigned char *data);

    unsigned char operator[](int pos);

    std::vector<unsigned char>::iterator begin();

    std::vector<unsigned char>::iterator end();

    void writeLength();

    /**
     * Turns the buffer into an array
     * Be sure to use Packet::size() when indexing array
     * @return buffer as an array
     */
    unsigned char *toArray();

    size_t size();

    size_t UnreadLength();

    void Reset(bool shouldReset = true);

    std::string to_string();

    int getId();

    void movePos(int amount);

    void print(const std::string &between = "\r\n");

// endregion
// region Write Data

    Packet &operator<<(unsigned char value);

    Packet &operator<<(short value);

    Packet &operator<<(int value);

    Packet &operator<<(long value);

    Packet &operator<<(float value);

    Packet &operator<<(bool value);

    Packet &operator<<(const std::string &value);

// endregion
// region Read Data

    unsigned char ReadByte(bool moveReadPos = true);

    unsigned char *ReadBytes(size_t length, bool moveReadPos = true);

    std::string readString(bool moveReadPos = true);

    unsigned int readUInt(bool moveReadPos = true);

    unsigned long readULong(bool moveReadPos = true);

    unsigned long long int readULongLong(bool moveReadPos = true);

    short readShort(bool moveReadPos = true);

    long readLong(bool moveReadPos = true);

    float readFloat(bool moveReadPos = true);

    bool readBool(bool moveReadPos = true);

// endregion

private:
// region Helpers
    void _write(unsigned char *value, size_t size) {
        buffer_.insert(buffer_.end(), value, value + size);
    }

    template<typename T>
    unsigned char *_toBytes(T in) {
        auto *p = reinterpret_cast<unsigned char *>(&in);
        auto *out = (unsigned char *) malloc(sizeof(T));
        for (int i = 0; i < sizeof(T); ++i) {
            out[i] = p[i];
        }
        return out;
    }

    template<typename T>
    T _read(bool moveReadPos = true) {
        unsigned char p[sizeof(T)];
        for (int i = 0; i < sizeof(T); ++i) {
            p[i] = buffer_[i + readPos_];
        }
        if (moveReadPos) readPos_ += sizeof(T);
        return *(T *) p;
    }

    template<typename T>
    T _read(int rev, bool moveReadPos) {
        unsigned char p[sizeof(T)];
        for (int i = 0; i < sizeof(T); ++i) {
            p[i] = buffer_[i + readPos_ - rev];
        }
        if (moveReadPos) readPos_ += sizeof(T);
        return *(T *) p;
    }

    template<typename T>
    T _read(int index) {
        unsigned char p[sizeof(T)];
        for (int i = 0; i < sizeof(T); ++i) {
            p[i] = buffer_[i + index];
        }
        return *(T *) p;
    }

    template<typename T>
    static T _read(std::vector<char> buffer, int index = 0) {
        unsigned char p[sizeof(T)];
        for (int i = 0; i < sizeof(T); ++i) {
            p[i] = buffer[i + index];
        }
        return *(T *) p;
    }

    /**
     * Used for padding strings with 2 extra null characters so that the string
     * can be recognised when decoded
     */
    void _pad() {
        buffer_.push_back('\0');
        buffer_.push_back('\0');
    }

// endregion
};

#endif //HAZELCHAIN_PACKET_H
