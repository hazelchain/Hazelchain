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

enum ServerPackets {
    welcome,
};

enum ClientPackets {
    welcomeReceived
};

class Packet {
private:
    std::vector<unsigned char> buffer_;
    unsigned char *readableBuffer_{};
    int readPos_;

    /**
     * Reads the following bytes of the readable buffer corresponding to the size of
     * the type passed in. read as little endian
     * @tparam T - Any primative type, except string
     * @param rev - How much spaces to go back into buffer, default is zero
     * @return the same type processed from the readable buffer in little endian
     * form
     */
    template<typename T>
    T _read(int rev = 0) {
        unsigned char p[sizeof(T)];
        for (int i = 0; i < sizeof(T); ++i) {
            p[i] = readableBuffer_[readPos_ - rev + i];
        }
        return (*(T *) p);
    }

public:
    Packet() {
        readPos_ = 0;
    }

    explicit Packet(int id_) {
        readPos_ = 0;

        Write(id_);
    }

// region functions

    void SetBytes(unsigned char data[]) {
        Write(data);
        readableBuffer_ = &buffer_[0];
    }

    void WriteLength() {
        buffer_.insert(buffer_.begin(), buffer_.size());
    }

    void InsertInt(int value) {
        buffer_.insert(buffer_.begin(), value);
    }

    unsigned char *toArray() {
        readableBuffer_ = &buffer_[0];
        return readableBuffer_;
    }

    size_t Length() {
        return buffer_.size();
    }

    size_t UnreadLength() {
        return Length() - readPos_;
    }

    void Reset(bool shouldReset = true) {
        if (shouldReset) {
            buffer_.clear();
            readableBuffer_ = nullptr;
            readPos_ = 0;
        } else {
            readPos_ -= 4;
        }
    }

// endregion
// region Write Data

    void Write(unsigned char *value, size_t size) {
        buffer_.insert(buffer_.end(), value, value + size);
    }

    void Write(unsigned char value) {
        buffer_.push_back(value);
    }

    void Write(short value) {
        Write(reinterpret_cast<unsigned char *>(&value), sizeof(short));
    }

    void Write(int value) {
        Write(reinterpret_cast<unsigned char *>(&value), sizeof(int));
    }

    void Write(long value) {
        Write(reinterpret_cast<unsigned char *>(&value), sizeof(long));
    }

    void Write(float value) {
        Write(reinterpret_cast<unsigned char *>(&value), sizeof(float));
    }

    void Write(bool value) {
        Write(reinterpret_cast<unsigned char *>(&value), sizeof(bool));
    }

    void Write(const std::string &value) {
        auto *p = value.c_str();
        if (value.size() > 1) {
            Write(reinterpret_cast<unsigned char *>(const_cast<char *>(p)), value.size() + 1);
        } else {
            Write(reinterpret_cast<unsigned char *>(p[0]), sizeof(char));
        }
    }

// endregion
// region Read Data

    unsigned char ReadByte(bool moveReadPos = true) {
        if (buffer_.size() > readPos_) {
            if (moveReadPos) ++readPos_;
            return _read<unsigned char>(1);
        } else {
            log(constants::logger, error)
                    << "Could not read value of type 'byte'!"
                    << logger::endl;
        }
    }

    unsigned char *ReadBytes(size_t length, bool moveReadPos = true) {
        if (buffer_.size() > readPos_) {
            std::vector<unsigned char> value(
                    &buffer_[readPos_],
                    &buffer_[readPos_] + length
            );
            if (moveReadPos) ++readPos_;
            unsigned char *out = &value[0];
            return out;
        } else {
            log(constants::logger, error)
                    << "Could not read value of type 'byte[]'!"
                    << logger::endl;
        }
    }

    short ReadShort(bool moveReadPos = true) {
        if (buffer_.size() > readPos_) {
            if (moveReadPos) readPos_ += 2;
            return _read<short>(2);
        } else {
            log(constants::logger, error)
                    << "Could not read value of type 'short'!"
                    << logger::endl;
        }
    }

    int ReadInt(bool moveReadPos = true) {
        if (buffer_.size() > readPos_) {
            return _read<int>(4);
        } else {
            log(constants::logger, error)
                    << "Could not read value of type 'int'!"
                    << logger::endl;
        }
    }

    long ReadLong(bool moveReadPos = true) {
        if (buffer_.size() > readPos_) {
            readPos_ += moveReadPos ? 8 : 0;
            return _read<long>(8);
        } else {
            log(constants::logger, error)
                    << "Could not read value of type 'long'!"
                    << logger::endl;
        }
    }

    float ReadFloat(bool moveReadPos = true) {
        if (buffer_.size() > readPos_) {

            readPos_ += moveReadPos ? 4 : 0;
            return _read<float>(4);
        } else {
            log(constants::logger, error)
                    << "Could not read value of type 'float'!"
                    << logger::endl;
        }
    }

    bool ReadBool(bool moveReadPos = true) {
        if (buffer_.size() > readPos_) {
            readPos_ += moveReadPos ? 1 : 0;
            return _read<bool>(1);
        } else {
            log(constants::logger, error)
                    << "Could not read value of type 'int'!"
                    << logger::endl;
        }
    }

// endregion
};

#endif //HAZELCHAIN_PACKET_H
