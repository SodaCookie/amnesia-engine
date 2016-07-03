#include "system.h"

System::System(std::string name, std::shared_ptr<Engine> engine) :
    name(name), engine(engine) {
}

void System::add_message(std::unique_ptr<IMessage> message) {
    messages.push_back(message);
}

std::vector<std::unique_ptr<IMessage>> System::flush_messages() {
    return_messages = messages;
    messages = std::vector<std::unique_ptr<IMessage>>();
    return return_messages
}
