#include "RegStatus.h"

RegStatus::RegStatus() {
	busy = false;
	Qi = 0;
}

RegStatus::RegStatus(int RegStatusEmpty) {

	Qi = RegStatusEmpty;
}