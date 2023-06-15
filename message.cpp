#pragma once
#include "message.h"
gvalue Message::getValue() { return value; }
Message::Message(gvalue g) { value = g; }

void MessageBus::addReceiver(function<void(Message)> messageReceiver) {
    receivers.push_back(messageReceiver);
}
void MessageBus::sendMessage(gvalue message) {
    messages.push(*new Message(message));
}
void MessageBus::notify() {
    while (!messages.empty()) {
        for (auto iter = receivers.begin(); iter != receivers.end(); iter++) {
            (*iter)(messages.front());
        }
        messages.pop();
    }
}
