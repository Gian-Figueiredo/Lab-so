
#define MODULE
#define LINUX


#include <linux/module.h> 
#include <linux/kernel.h>  

static int __init principio_de_tudo(void) {
  printk("<1> Hello world 1.\n");
  return 0;
}

static void __exit no_fim_era_so_eu(void) {
  printk(KERN_ALERT "Goodbye world 1.\n");
}

module_init(principio_de_tudo);
module_exit(no_fim_era_so_eu);

MODULE_LICENSE("GPL");
