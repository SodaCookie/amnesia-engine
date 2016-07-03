#include "system.h"

System::System(std::string name) :
    name(name) {
}

void System::add_message(std::shared_ptr<IMessage> message) {
    messages.push_back(message);
}

std::vector<std::shared_ptr<IMessage>> System::flush_messages() {
    auto return_messages = messages;
    messages = std::vector<std::shared_ptr<IMessage>>();
    return return_messages;
}
