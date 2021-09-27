//
// Created by chris on 2021-09-07.
//

#include "Packet.h"
#include "../constants.h"
#include "../storage/logging/Logger.h"

// region Constructors

Packet::Packet(int id)
        : writable_(true), id(id) {
    this->operator<<(PROTOCOL_VERSION);
    this->operator<<(id);
}

Packet::Packet(std::vector<char> in)
        : writable_(false) {
    if (PROTOCOL_VERSION < _read<int>(in, 0)) {
        log(constants::logger, error)
                << "Incompatible protocol version"
                << std::endl;
        return;
    }

    id = _read<int>(in, 4);
    size_ = _read<int>(in, 8);

    buffer_ = std::vector<unsigned char>(
            in.begin(),
            in.begin() + HEADER_SIZE + size_
    );

    movePos(HEADER_SIZE);
}

// endregion
// region functions

void Packet::SetBytes(unsigned char *data) {
    buffer_ = std::vector<unsigned char>(
            data,
            data + (sizeof(data) / sizeof(data[0]))
    );
}

unsigned char Packet::operator[](int pos) {
    return buffer_[pos];
}

std::vector<unsigned char>::iterator Packet::begin() {
    return buffer_.begin();
}

std::vector<unsigned char>::iterator Packet::end() {
    return buffer_.end();
}

void Packet::writeLength() {
    auto *size = _toBytes((int) buffer_.size() - (HEADER_SIZE - INT_SIZE));
    std::cout << sizeof(size) << "\n\n\n" << std::endl;
    buffer_.insert(
            buffer_.begin() + (HEADER_SIZE - INT_SIZE),
            size,
            size + sizeof(size) / 2
    );
}

unsigned char *Packet::toArray() {
    return &buffer_[0];
}

size_t Packet::size() {
    return -1 != size_ ? size_ : buffer_.size();
//    return buffer_.size();
}

size_t Packet::UnreadLength() {
    return size() - readPos_;
}

void Packet::Reset(bool shouldReset) {
    if (shouldReset) {
        buffer_.clear();
        readPos_ = 0;
    } else {
        readPos_ -= 4;
    }
}

std::string Packet::to_string() {
    std::stringstream ss;
    for (auto &i: buffer_) {
        ss << std::setw(2) << std::setfill('0') << std::hex
           << "0x" << (int) i << " ";
    }
    return ss.str();
}

int Packet::getId() {
    return _read<int>(4);
}

void Packet::movePos(int amount) {
    readPos_ += amount;
}

void Packet::print(const std::string &between) {
    for (auto i: *this) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << "0x" << (int) i
                  << std::dec << between;
    }
    if (between != "\r\n") std::cout << std::endl;
}

// endregion
//region Write

Packet &Packet::operator<<(unsigned char value) {
    if (!writable_) return *this; // throw error
    operator<<((int) value);
    return *this;
}

Packet &Packet::operator<<(short value) {
    if (!writable_) return *this; // throw error
    _write(reinterpret_cast<unsigned char *>(&value), sizeof(short));
    return *this;
}

Packet &Packet::operator<<(int value) {
    if (!writable_) return *this; // throw error
    _write(reinterpret_cast<unsigned char *>(&value), INT_SIZE);
    return *this;
}

Packet &Packet::operator<<(long value) {
    if (!writable_) return *this; // throw error
    _write(reinterpret_cast<unsigned char *>(&value), sizeof(long));
    return *this;
}

Packet &Packet::operator<<(float value) {
    if (!writable_) return *this; // throw error
    _write(reinterpret_cast<unsigned char *>(&value), sizeof(float));
    return *this;
}

Packet &Packet::operator<<(bool value) {
    if (!writable_) return *this; // throw error
    _write(reinterpret_cast<unsigned char *>(&value), sizeof(bool));
    return *this;
}

Packet &Packet::operator<<(const std::string &value) {
    if (!writable_) return *this; // throw error
    auto *str = (unsigned char *) value.c_str();
    _write(str, value.size());
    this->_pad();
    return *this;
}

// endregion
// region Read

unsigned char Packet::ReadByte(bool moveReadPos) {
    if (buffer_.size() > readPos_) {
        if (moveReadPos) ++readPos_;
        return _read<unsigned char>(moveReadPos, 1);
    }
    return '\0';
}

unsigned char *Packet::ReadBytes(size_t length, bool moveReadPos) {
    if (buffer_.size() > readPos_) {
        std::vector<unsigned char> value(
                &buffer_[readPos_],
                &buffer_[readPos_] + length
        );
        if (moveReadPos) ++readPos_;
        unsigned char *out = &value[0];
        return out;
    } else {
    }
    return nullptr;
}

std::string Packet::readString(bool moveReadPos) {
    std::string out;
    unsigned int startReadPos = readPos_;
    if (buffer_.size() > readPos_) {
        while (readPos_ < buffer_.size()) {
            std::string p(&buffer_[readPos_], &buffer_[readPos_] + 4);
            if (p.at(0) == '\0' &&
                p.at(1) == '\0' &&
                p.at(2) == '\0' &&
                p.at(3) == '\0')
                break;
            out += p[0];
            ++readPos_;
        }
    }

    if (!moveReadPos) readPos_ = startReadPos;
    return out;
}

unsigned int Packet::readUInt(bool moveReadPos) {
    return _read<unsigned int>();
}

unsigned long Packet::readULong(bool moveReadPos) {
    return _read<unsigned long>();
}

unsigned long long int Packet::readULongLong(bool moveReadPos) {
    return _read<unsigned long long int>();
}

// endregion