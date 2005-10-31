--- kqemu-freebsd.c.orig	Mon Aug 15 01:34:06 2005
+++ kqemu-freebsd.c	Tue Oct 25 21:08:43 2005
@@ -3,32 +3,55 @@
 #include <sys/param.h>
 #include <sys/systm.h>
 #include <sys/conf.h>
+#include <sys/ctype.h>
+#include <sys/fcntl.h>
 #include <sys/ioccom.h>
 #include <sys/malloc.h>
 #include <sys/module.h>
+#if __FreeBSD_version >= 500000
 #include <sys/mutex.h>
+#endif
 #include <sys/proc.h>
+#include <sys/resourcevar.h>
+#if __FreeBSD_version >= 500000
 #include <sys/sched.h>
+#endif
 #include <sys/signalvar.h>
 #include <sys/kernel.h>
+#include <sys/sysctl.h>
+#include <sys/uio.h>
+#if __FreeBSD_version < 500000
+#include <sys/buf.h>
+#endif
+
 #include <vm/vm.h>
 #include <vm/vm_param.h>
 #include <vm/vm_extern.h>
 #include <vm/pmap.h>
 #include <vm/vm_map.h>
 #include <vm/vm_kern.h>
+#include <vm/vm_page.h>
+
 #include <machine/vmparam.h>
 #include <machine/stdarg.h>
 
 #include "kqemu-kernel.h"
 
+#ifndef KQEMU_MAJOR
+#define KQEMU_MAJOR 250
+#endif
+
 MALLOC_DECLARE(M_KQEMU);
 MALLOC_DEFINE(M_KQEMU, "kqemu", "kqemu buffers");
 
+int kqemu_debug;
+SYSCTL_INT(_debug, OID_AUTO, kqemu_debug, CTLFLAG_RW, &kqemu_debug, 0,
+        "kqemu debug flag");
+
 #define	USER_BASE	0x1000
 
 /* lock the page at virtual address 'user_addr' and return its
-   physical page index. Return -1 if error */
+   physical page index. Return NULL if error */
 struct kqemu_user_page *CDECL kqemu_lock_user_page(unsigned long *ppage_index,
                                                    unsigned long user_addr)
 {
@@ -37,14 +60,18 @@
     vm_paddr_t pa = 0;
     int ret;
     pmap_t pmap;
+#if __FreeBSD_version >= 500000
     ret = vm_map_wire(&vm->vm_map, va, va+PAGE_SIZE, VM_MAP_WIRE_USER);
+#else
+    ret = vm_map_user_pageable(&vm->vm_map, va, va+PAGE_SIZE, FALSE);
+#endif
     if (ret != KERN_SUCCESS) {
-	printf("kqemu_lock_user_page(%08lx) failed, ret=%d\n", user_addr, ret);
+	kqemu_log("kqemu_lock_user_page(%08lx) failed, ret=%d\n", user_addr, ret);
 	return NULL;
     }
     pmap = vm_map_pmap(&vm->vm_map);
     pa = pmap_extract(pmap, va);
-    // printf("kqemu_lock_user_page(%08lx) va=%08x pa=%08x\n", user_addr, va, pa);
+    /* kqemu_log("kqemu_lock_user_page(%08lx) va=%08x pa=%08x\n", user_addr, va, pa); */
     *ppage_index = pa >> PAGE_SHIFT;
     return (struct kqemu_user_page *)va;
 }
@@ -54,12 +81,16 @@
     struct vmspace *vm = curproc->p_vmspace;
     vm_offset_t va;
     int ret;
-    // printf("kqemu_unlock_user_page(%08lx)\n", page_index);
+    /* kqemu_log("kqemu_unlock_user_page(%08lx)\n", page_index); */
     va = (vm_offset_t)page;
+#if __FreeBSD_version >= 500000
     ret = vm_map_unwire(&vm->vm_map, va, va+PAGE_SIZE, VM_MAP_WIRE_USER);
+#else
+    ret = vm_map_user_pageable(&vm->vm_map, va, va+PAGE_SIZE, TRUE);
+#endif
 #if 0
     if (ret != KERN_SUCCESS) {
-	printf("kqemu_unlock_user_page(%08lx) failed, ret=%d\n", page_index, ret);
+	kqemu_log("kqemu_unlock_user_page(%08lx) failed, ret=%d\n", page_index, ret);
     }
 #endif
 }
@@ -76,20 +107,21 @@
 
     va = kmem_alloc(kernel_map, PAGE_SIZE);
     if (va == 0) {
-	printf("kqemu_alloc_zeroed_page: NULL\n");
-	return -1;
+	kqemu_log("kqemu_alloc_zeroed_page: NULL\n");
+	return NULL;
     }
     pmap = vm_map_pmap(kernel_map);
     pa = pmap_extract(pmap, va);
-    // printf("kqemu_alloc_zeroed_page: %08x\n", pa);
+    /* kqemu_log("kqemu_alloc_zeroed_page: %08x\n", pa); */
     *ppage_index = pa >> PAGE_SHIFT;
     return (struct kqemu_page *)va;
 }
 
 void CDECL kqemu_free_page(struct kqemu_page *page)
 {
-    //    printf("kqemu_free_page(%08lx)\n", page_index);
-    /* XXX: do it */
+    if (kqemu_debug > 0)
+    	kqemu_log("kqemu_free_page(%p)\n", page);
+    kmem_free(kernel_map, (vm_offset_t) page, PAGE_SIZE);
 }
 
 /* return kernel address of the physical page page_index */
@@ -103,42 +135,29 @@
    GB of physical memory */
 void * CDECL kqemu_vmalloc(unsigned int size)
 {
-    struct vmspace *vm = curproc->p_vmspace;
-    vm_offset_t va = USER_BASE;
-    int rv;
-    if (size % PAGE_SIZE != 0) {
-	printf("kqemu_vmalloc(%d) not a multiple of page size\n", size);
-	return NULL;
-    }
-    rv = vm_map_find(&vm->vm_map, NULL, 0, &va, size, 1,
-		     VM_PROT_ALL, VM_PROT_ALL, 0);
-    if (rv != KERN_SUCCESS) {
-	printf("kqemu_vmalloc(%d) failed rv=%d\n", size, rv);
-	return NULL;
-    }
-    printf("kqemu_vmalloc(%d): %08x\n", size, va);
-    return (void *)va;
+    void *ptr = malloc(size, M_KQEMU, M_WAITOK);
+    if (kqemu_debug > 0)
+	kqemu_log("kqemu_vmalloc(%d): %p\n", size, ptr);
+    return ptr;
 }
 
 void CDECL kqemu_vfree(void *ptr)
 {
-    printf("kqemu_vfree(%p)\n", ptr);
+    if (kqemu_debug > 0)
+	kqemu_log("kqemu_vfree(%p)\n", ptr);
+    free(ptr, M_KQEMU);
 }
 
 /* return the physical page index for a given virtual page */
 unsigned long CDECL kqemu_vmalloc_to_phys(const void *vaddr)
 {
-    struct vmspace *vm = curproc->p_vmspace;
-    vm_paddr_t pa;
-    pmap_t pmap;
-
-    pmap = vm_map_pmap(&vm->vm_map);
-    pa = pmap_extract(pmap, (vm_offset_t)vaddr);
+    vm_paddr_t pa = vtophys(vaddr);
     if (pa == 0) {
-	printf("kqemu_vmalloc_to_phys(%p)->error\n", vaddr);
+	kqemu_log("kqemu_vmalloc_to_phys(%p)->error\n", vaddr);
 	return -1;
     }
-    printf("kqemu_vmalloc_to_phys(%p)->%08x\n", vaddr, pa);
+    if (kqemu_debug > 0)
+	kqemu_log("kqemu_vmalloc_to_phys(%p)->%08x\n", vaddr, pa);
     return pa >> PAGE_SHIFT;
 }
 
@@ -154,16 +173,48 @@
 {
 }
 
+#if __FreeBSD_version < 500000
+static int
+curpriority_cmp(struct proc *p)
+{
+    int c_class, p_class;
+
+    c_class = RTP_PRIO_BASE(curproc->p_rtprio.type);
+    p_class = RTP_PRIO_BASE(p->p_rtprio.type);
+    if (p_class != c_class)
+	return (p_class - c_class);
+    if (p_class == RTP_PRIO_NORMAL)
+	return (((int)p->p_priority - (int)curpriority) / PPQ);
+    return ((int)p->p_rtprio.prio - (int)curproc->p_rtprio.prio);
+}
+
+/* return TRUE if a signal is pending (i.e. the guest must stop
+   execution) */
+int CDECL kqemu_schedule(void)
+{
+    struct proc *p = curproc;
+    if (curpriority_cmp(p) > 0) {
+	int s = splhigh();
+	p->p_priority = MAXPRI;
+	setrunqueue(p);
+	p->p_stats->p_ru.ru_nvcsw++;
+	mi_switch();
+	splx(s);
+    }
+    return issignal(curproc) != 0;
+}
+#else
 /* return TRUE if a signal is pending (i.e. the guest must stop
    execution) */
 int CDECL kqemu_schedule(void)
 {
-    // printf("kqemu_schedule\n");
+    /* kqemu_log("kqemu_schedule\n"); */
     mtx_lock_spin(&sched_lock);
     mi_switch(SW_VOL, NULL);
     mtx_unlock_spin(&sched_lock);
     return SIGPENDING(curthread);
 }
+#endif
 
 static char log_buf[4096];
 
@@ -176,47 +227,159 @@
     va_end(ap);
 }
 
+#define KQEMU_MAX_INSTANCES 4
+
 struct kqemu_instance { 
-    //    struct semaphore sem;  
+#if __FreeBSD_version >= 500000
+    TAILQ_ENTRY(kqemu_instance) kqemu_ent;
+    struct cdev *kqemu_dev;
+#endif
+    /*    struct semaphore sem;  */
     struct kqemu_state *state;
 };
 
+static int kqemu_ref_count = 0;
+static int max_locked_pages;
+
+#if __FreeBSD_version < 500000
+static dev_t kqemu_dev;
+#else
+static struct clonedevs *kqemuclones;
+static TAILQ_HEAD(,kqemu_instance) kqemuhead = TAILQ_HEAD_INITIALIZER(kqemuhead);
+static eventhandler_tag clonetag;
+#endif
+
 static d_close_t kqemu_close;
 static d_open_t kqemu_open;
 static d_ioctl_t kqemu_ioctl;
 
 static struct cdevsw kqemu_cdevsw = {
+#if __FreeBSD_version < 500000
+	/* open */	kqemu_open,
+	/* close */	kqemu_close,
+	/* read */	noread,
+	/* write */	nowrite,
+	/* ioctl */	kqemu_ioctl,
+	/* poll */	nopoll,
+	/* mmap */	nommap,
+	/* strategy */	nostrategy,
+	/* name */	"kqemu",
+	/* maj */	KQEMU_MAJOR,
+	/* dump */	nodump,
+	/* psize */	nopsize,
+	/* flags */	0,
+	/* bmaj */	-1
+#else
 	.d_version =	D_VERSION,
 	.d_flags =	D_NEEDGIANT,
 	.d_open =	kqemu_open,
 	.d_ioctl =	kqemu_ioctl,
 	.d_close =	kqemu_close,
 	.d_name =	"kqemu"
+#endif
 };
 
-/* For use with make_dev(9)/destroy_dev(9). */
-static struct cdev *kqemu_dev;
+#if __FreeBSD_version >= 500000
+static void
+#if __FreeBSD_version >= 600034
+kqemu_clone(void *arg, struct ucred *cred, char *name, int namelen,
+struct cdev **dev)
+#else
+kqemu_clone(void *arg, char *name, int namelen, struct cdev **dev)
+#endif
+{
+    int unit, r;
+    if (*dev != NULL)
+	return;
+
+    if (strcmp(name, "kqemu") == 0)
+	unit = -1;
+    else if (dev_stdclone(name, NULL, "kqemu", &unit) != 1)
+	return;         /* Bad name */
+    if (unit != -1 && unit > KQEMU_MAX_INSTANCES)
+	return;
+
+    r = clone_create(&kqemuclones, &kqemu_cdevsw, &unit, dev, 0);
+    if (r) {
+	*dev = make_dev(&kqemu_cdevsw, unit2minor(unit),
+	    UID_ROOT, GID_WHEEL, 0660, "kqemu%d", unit);
+	if (*dev != NULL) {
+	    (*dev)->si_flags |= SI_CHEAPCLONE;
+	}
+    }
+}
+#endif
+
+static void kqemu_destroy(struct kqemu_instance *ks)
+{
+#if __FreeBSD_version >= 500000
+    struct cdev *dev = ks->kqemu_dev;
+#endif
+
+    if (ks->state) {
+        kqemu_delete(ks->state);
+        ks->state = NULL;
+    }
+
+#if __FreeBSD_version >= 500000
+    dev->si_drv1 = NULL;
+    TAILQ_REMOVE(&kqemuhead, ks, kqemu_ent);
+    destroy_dev(dev);
+#endif
+    free(ks, M_KQEMU);
+    --kqemu_ref_count;
+}
 
 /* ARGSUSED */
 static int
+#if __FreeBSD_version < 500000
+kqemu_open(dev_t dev, int flags, int fmt __unused, struct proc *p)
+{
+#else
 kqemu_open(struct cdev *dev, int flags, int fmt __unused,
     struct thread *td)
 {
+    struct proc	*p = td->td_proc;
+#endif
     struct kqemu_instance *ks;
+
+#if __FreeBSD_version >= 500000
+    if (kqemu_ref_count >= KQEMU_MAX_INSTANCES)
+#else
+    if (dev->si_drv1 || kqemu_ref_count >= KQEMU_MAX_INSTANCES)
+#endif
+	return(EBUSY);
+
+    if ((flags & (FREAD|FWRITE)) == FREAD)
+	return(EPERM);
+
     ks = malloc(sizeof(struct kqemu_instance), M_KQEMU, M_WAITOK);
     if (ks == NULL) {
-	printf("malloc failed\n");
+	kqemu_log("malloc failed\n");
 	return ENOMEM;
     }
-    ks->state = NULL;
+    memset(ks, 0, sizeof *ks);
+#if __FreeBSD_version >= 500000
+    ks->kqemu_dev = dev;
+    TAILQ_INSERT_TAIL(&kqemuhead, ks, kqemu_ent);
+#endif
+    kqemu_ref_count++;
+
     dev->si_drv1 = ks;
+    if (kqemu_debug > 0)
+	kqemu_log("opened by pid=%d\n", p->p_pid);
     return 0;
 }
 
 /* ARGSUSED */
 static int
+#if __FreeBSD_version < 500000
+kqemu_ioctl(dev_t dev, u_long cmd, caddr_t addr,
+    int flags __unused, struct proc *p)
+#else
 kqemu_ioctl(struct cdev *dev, u_long cmd, caddr_t addr, 
     int flags __unused, struct thread *td)
+#endif
 {
     int error = 0;
     int ret;
@@ -231,8 +394,9 @@
 	    break;
 	}
 	d1 = *(struct kqemu_init *)addr;
-	printf("ram_base=%p ram_size=%ld\n", d1.ram_base, d1.ram_size);
-	s = kqemu_init(d, 16000);
+	if (kqemu_debug > 0)
+	    kqemu_log("ram_base=%p ram_size=%ld\n", d1.ram_base, d1.ram_size);
+	s = kqemu_init(d, max_locked_pages);
 	if (s == NULL) {
 	    error = ENOMEM;
 	    break;
@@ -248,9 +412,16 @@
 	}
 	ctx = kqemu_get_cpu_state(s);
 	*ctx = *(struct kqemu_cpu_state *)addr;
+#if __FreeBSD_version >= 500000
 	DROP_GIANT();
+#endif
 	ret = kqemu_exec(s);
+#if __FreeBSD_version >= 500000
 	PICKUP_GIANT();
+	td->td_retval[0] = ret;
+#else
+	p->p_retval[0] = ret;
+#endif
 	*(struct kqemu_cpu_state *)addr = *ctx;
 	break;
     }
@@ -265,10 +436,22 @@
 
 /* ARGSUSED */
 static int
+#if __FreeBSD_version < 500000
+kqemu_close(dev_t dev, int flags, int fmt __unused, struct proc *p)
+{
+#else
 kqemu_close(struct cdev *dev __unused, int flags, int fmt __unused,
     struct thread *td)
 {
-	return 0;
+    struct proc     *p = td->td_proc;
+#endif
+    struct kqemu_instance *ks = (struct kqemu_instance *) dev->si_drv1;
+
+    kqemu_destroy(ks);
+
+    if (kqemu_debug > 0)
+	kqemu_log("closed by pid=%d\n", p->p_pid);
+    return 0;
 }
 
 /* ARGSUSED */
@@ -276,15 +459,55 @@
 kqemu_modevent(module_t mod __unused, int type, void *data __unused)
 {
     int error = 0;
+#if __FreeBSD_version < 500000
+    int rc;
+#else
+    struct kqemu_instance *ks;
+#endif
 
     switch (type) {
     case MOD_LOAD:
 	printf("kqemu version 0x%08x\n", KQEMU_VERSION);
+	max_locked_pages = physmem / (2 * KQEMU_MAX_INSTANCES);
+	if (max_locked_pages > 32768)
+	    max_locked_pages = 32768;
+#if __FreeBSD_version < 500000
+	if ((rc = cdevsw_add(&kqemu_cdevsw))) {
+	    kqemu_log("error registering cdevsw, rc=%d\n", rc);
+            error = ENOENT;
+            break;
+	}
 	kqemu_dev = make_dev(&kqemu_cdevsw, 0,
-			     UID_ROOT, GID_WHEEL, 0666, "kqemu");
+			     UID_ROOT, GID_WHEEL, 0660, "kqemu");
+#else
+	clone_setup(&kqemuclones);
+	clonetag = EVENTHANDLER_REGISTER(dev_clone, kqemu_clone, 0, 1000);
+	if (!clonetag) {
+            error = ENOMEM;
+	    break;
+	}
+#endif
+	kqemu_log("KQEMU installed, max_instances=%d max_locked_mem=%dkB.\n",
+		  KQEMU_MAX_INSTANCES, max_locked_pages * 4);
+
+	kqemu_ref_count = 0;
 	break;
     case MOD_UNLOAD:
+	if (kqemu_ref_count > 0) {
+            error = EBUSY;
+            break;
+        }
+#if __FreeBSD_version < 500000
 	destroy_dev(kqemu_dev);
+	if ((rc = cdevsw_remove(&kqemu_cdevsw)))
+	    kqemu_log("error unregistering, rc=%d\n", rc);
+#else
+	EVENTHANDLER_DEREGISTER(dev_clone, clonetag);
+	while ((ks = TAILQ_FIRST(&kqemuhead)) != NULL) {
+	    kqemu_destroy(ks);
+	}
+	clone_cleanup(&kqemuclones);
+#endif
 	break;
     case MOD_SHUTDOWN:
 	break;
