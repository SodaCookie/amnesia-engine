#ifndef _AMNESIA_MESSAGE_HEADER_
#define _AMNESIA_MESSAGE_HEADER_

#include <string>
#include <tuple>

class IMessage {

public:

    IMessage(std::string mtype) : mtype(mtype) {
    }

    std::string mtype;

};

template <typename... Types>
class Message : public IMessage {

public:

    Message(std::string mtype, Types... args) : IMessage(mtype) {
        data = std::tuple<Types...>(args...);
    }
    std::tuple<Types ...> data;

};

#endif