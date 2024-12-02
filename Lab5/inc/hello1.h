#ifndef HELLO1_H
#define HELLO1_H

#include <linux/list.h>
#include <linux/ktime.h>

struct array_node {
	struct list_head node;
        ktime_t timepointer;
        ktime_t execution_duration;
};

void print_hello(unsigned int val);

#endif
