#pragma once

#include <functional>
#include <queue>
#include <vector>

using std::queue;
using std::vector;
using std::function;

enum gvalue { QUIT, PUP, PDOWN, PLEFT, PRIGHT, RUP, RDOWN, RLEFT, RRIGHT };

class Message {
	gvalue value;
public:
	gvalue getValue();
	Message(gvalue g);
};

class MessageBus {
	vector<function<void(Message)>> receivers;
	queue<Message> messages;
public:
	void addReceiver(function<void(Message)> receiver);
	void sendMessage(gvalue message);
	void notify();
};