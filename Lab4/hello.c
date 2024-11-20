#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>

MODULE_AUTHOR("Kateryna Demianenko <demianenko.kateruna@lll.kpi.ua>");
MODULE_DESCRIPTION("'Hello, world!' in Linux Kernel created for Lab4");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int val = 1;

module_param(val, uint, 0444);
MODULE_PARM_DESC(val, "How many times to repeat 'Hello, world!' ?");

struct array_node {
	struct list_head node;
        ktime_t timepointer;	
};

static LIST_HEAD(Head_Node);

static int __init hello_init(void)
{
	 int count;

	 if (val == 0 || (val >= 5 && val <= 10) ) {
		printk(KERN_WARNING "Warning! The optimal amount is less than 5.\n");
	 } else if (val > 10) {
		printk(KERN_ERR "Error! Your number is too large.\n");
		return -EINVAL;
	 }

	 for (count = 0; count < val; count++) {
		struct array_node *linkedlist = kmalloc(sizeof(*linkedlist), GFP_KERNEL);

		linkedlist->timepointer = ktime_get();
		list_add(&linkedlist->node, &Head_Node);
		printk(KERN_EMERG "Hello, world!\n");
	 }

	 return 0;
}

static void __exit hello_exit(void)
{
	struct array_node *linkedlist, *tmp;

	list_for_each_entry_safe(linkedlist, tmp, &Head_Node, node) {
		ktime_t duration = ktime_sub(ktime_get(), linkedlist->timepointer);
        
		printk(KERN_INFO "Elapsed time: %lld ns\n", ktime_to_ns(duration));
		list_del(&linkedlist->node);
		kfree(linkedlist);
	}
}

module_init(hello_init);
module_exit(hello_exit);
