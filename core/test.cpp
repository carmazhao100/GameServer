#include"gsQueue.h"

int main() {
	affair_queue * q = new affair_queue();
	int fd = 0;
	uint_32	 size = 0;
	int_8 * content = new int_8[1];

	proxyMsg* p = new proxyMsg(content , size , fd);
	q->push(p);
	delete q;
	return 0;
}
