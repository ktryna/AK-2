#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include "hello1.h"

MODULE_AUTHOR("Kateryna Demianenko <demianenko.kateruna@lll.kpi.ua>");
MODULE_DESCRIPTION("'Hello, world!' in Linux Kernel created for Lab4");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int val = 1;

module_param(val, uint, 0444);
MODULE_PARM_DESC(val, "How many times to repeat 'Hello, world!' ?");

static int __init hello2_init(void)
{
	pr_info("Module 'hello2' has already loaded.\n");	
	
	if (val == 0 || (val >= 5 && val <= 10) ) {
		pr_warn("Warning! The optimal amount is less than 5.\n");
	} else if (val > 10) {
		pr_err("Error! Your number is too large.\n");
		return -EINVAL;
	}
	
	print_hello(val);

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Module 'hello2' has already unloaded.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
