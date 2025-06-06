#include <linux/module.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>

#define NUM_THREADS 4

static struct task_struct *kth_arr[NUM_THREADS];

int thread_function(void *idx) {
    unsigned int i = 0;
    int t_id = *(int *)idx;

    printk(KERN_INFO "Thread %d iniciado com PID: %d\n", t_id, current->pid);

    while (!kthread_should_stop()) {
        printk(KERN_INFO "Thread %d ainda rodando... %d segundos\n", t_id, i);
        i++;
        if (i == 30)
            break;
        msleep(1000);
    }

    printk(KERN_INFO "Thread %d parando (PID: %d)\n", t_id, current->pid);
    return 0;
}

int initialize_thread(int idx) {
    char th_name[20];
    int *thread_id;

    // alocar ID dinamicamente para cada thread
    thread_id = kmalloc(sizeof(int), GFP_KERNEL);
    if (!thread_id)
        return -ENOMEM;

    *thread_id = idx;
    sprintf(th_name, "kthread_%d", idx);

    kth_arr[idx] = kthread_create(thread_function, (void *)thread_id, th_name);
    if (IS_ERR(kth_arr[idx])) {
        printk(KERN_ERR "Falha ao criar thread %d\n", idx);
        kfree(thread_id);
        return PTR_ERR(kth_arr[idx]);
    }

    wake_up_process(kth_arr[idx]);
    printk(KERN_INFO "Thread %d (%s) está rodando\n", idx, th_name);
    return 0;
}

static int __init mod_init(void) {
    int i;
    printk(KERN_INFO "Iniciando módulo de threads\n");
    for (i = 0; i < NUM_THREADS; i++) {
        if (initialize_thread(i) < 0) {
            printk(KERN_ERR "Erro ao inicializar thread %d\n", i);
            return -1;
        }
    }
    printk(KERN_INFO "Todas as threads foram iniciadas\n");
    return 0;
}

static void __exit mod_exit(void) {
    int i;
    printk(KERN_INFO "Encerrando módulo de threads\n");
    for (i = 0; i < NUM_THREADS; i++) {
        if (kth_arr[i]) {
            int ret = kthread_stop(kth_arr[i]);
            if (ret != -EINTR) {
                printk(KERN_INFO "Thread %d finalizada\n", i);
            } else {
                printk(KERN_WARNING "Não foi possível parar a thread %d\n", i);
            }
        }
    }
    printk(KERN_INFO "Todas as threads foram encerradas\n");
}

MODULE_LICENSE("GPL");

module_init(mod_init);
module_exit(mod_exit);
