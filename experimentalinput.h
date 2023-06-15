#pragma once
#include <vector>
#include <functional>
#include "inputcodes.h"

using std::function;
using std::vector;

typedef void (*Outcome)();

struct ExperimentalBind {
	int keyValue;
	Outcome outcome;
};

class ExperimentalConfiguration {
	vector<ExperimentalBind> binds;
public:
	void evaluate(function<int()> getInput);
};

class ExperimentalInput {	
	ExperimentalConfiguration current;
public:
	// initialize or override the current set of binds
	void set(ExperimentalConfiguration config);
	ExperimentalInput(ExperimentalConfiguration config);
};