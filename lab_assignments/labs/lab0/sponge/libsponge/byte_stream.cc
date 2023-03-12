#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) : streams(), capa(capacity), written_bytes(0), read_bytes(0), end(false) {}

size_t ByteStream::write(const string &data) {
    size_t can_write = capa - streams.size();
    size_t real_write = min(can_write, data.length());
    for (size_t i = 0; i < real_write; i++) {
        streams.push_back(data[i]);
    }
    written_bytes += real_write;
    return real_write;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t can_peek = min(len, streams.size());
    string output = "";
    size_t i = 0;
    while (i < can_peek) {
        output += streams[i];
        i++;
    }
    return output;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    if (len > streams.size()) {
        set_error();
        return;
    }
    size_t i = 0;
    while (i < len) {
        streams.pop_front();
        i++;
    }
    read_bytes += len;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    std::string readed_str = peek_output(len);
    pop_output(len);
    return readed_str;
}

void ByteStream::end_input() { end = true; }

bool ByteStream::input_ended() const { return end; }

size_t ByteStream::buffer_size() const { return streams.size(); }

bool ByteStream::buffer_empty() const { return streams.empty(); }

bool ByteStream::eof() const { return streams.empty() && end; }

size_t ByteStream::bytes_written() const { return written_bytes; }

size_t ByteStream::bytes_read() const { return read_bytes; }

size_t ByteStream::remaining_capacity() const { return capa - streams.size(); }
