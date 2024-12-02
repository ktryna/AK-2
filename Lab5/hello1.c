#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include "hello1.h"

MODULE_AUTHOR("Kateryna Demianenko <demianenko.kateruna@lll.kpi.ua>");
MODULE_DESCRIPTION("Lab5. Function print_hello() for module 'hello2'.");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(Head_Node);

void print_hello(unsigned int val)
{	
	int count;	
	
	for (count = 0; count < val; count++) {
		struct array_node *linkedlist = kmalloc(sizeof(*linkedlist), GFP_KERNEL);

		linkedlist->timepointer = ktime_get();
		list_add(&linkedlist->node, &Head_Node);
		pr_emerg("Hello, world!\n");
		linkedlist->execution_duration = ktime_sub(ktime_get(), linkedlist->timepointer);
	}
}

EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	 
	 pr_info("Module 'hello1' has already loaded.\n");
	 return 0;
}

static void __exit hello1_exit(void)
{
	struct array_node *linkedlist, *tmp;

	list_for_each_entry_safe(linkedlist, tmp, &Head_Node, node) {
		ktime_t duration = ktime_sub(ktime_get(), linkedlist->timepointer);
        
		pr_info(
			"Elapsed time: %lld ns.\n Elapsed time for printing: %lld ns.\n",
		 	ktime_to_ns(duration),
		 	ktime_to_ns(linkedlist->execution_duration)
		 	);
		 	
		list_del(&linkedlist->node);
		kfree(linkedlist);
	}
	
	pr_info("Module 'hello1' has already unloaded.\n");
}

module_init(hello1_init);
module_exit(hello1_exit);
