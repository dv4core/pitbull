#include "experimentalinput.h"

void ExperimentalConfiguration::evaluate(function<int()> getInput) {
	for (auto iter = binds.begin(); iter != binds.end(); iter++) {
		auto current = *iter;
		if (getInput() == current.keyValue) {
			current.outcome();
		}
	}
}

