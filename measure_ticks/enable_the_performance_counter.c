/*  
 *  hello-2.c - Demonstrating the module_init() and module_exit() macros.
 *  This is preferred over using init_module() and cleanup_module().
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>		/* Needed for the macros */

static int __init enable_the_performance_counter_init(void)
{
    /* enable user-mode access to the performance counter*/
    asm ("MCR p15, 0, %0, C9, C14, 0\n\t" :: "r"(1)); 

    /* disable counter overflow interrupts (just in case)*/
    asm ("MCR p15, 0, %0, C9, C14, 2\n\t" :: "r"(0x8000000f));
    printk(KERN_INFO "Enable the performance counter\n");
	return 0;
}

static void __exit enable_the_performance_counter_exit(void)
{
    /* enable user-mode access to the performance counter*/
    asm ("MCR p15, 0, %0, C9, C14, 0\n\t" :: "r"(0)); 
	printk(KERN_INFO "Disable the performance counter\n");
}

module_init(enable_the_performance_counter_init);
module_exit(enable_the_performance_counter_exit);
