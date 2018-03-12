#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x14522340, "module_layout" },
	{ 0x9853b40d, "d_path" },
	{ 0x4f1939c7, "per_cpu__current_task" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x25ec1b28, "strlen" },
	{ 0x7e5e301f, "unregister_kprobe" },
	{ 0xd691cba2, "malloc_sizes" },
	{ 0x93260715, "register_kprobe" },
	{ 0x973873ab, "_spin_lock" },
	{ 0x1a6d6e4f, "remove_proc_entry" },
	{ 0x3758301, "mutex_unlock" },
	{ 0x999e8297, "vfree" },
	{ 0x70db5817, "path_get" },
	{ 0xe2d5255a, "strcmp" },
	{ 0xed113e22, "proc_mkdir" },
	{ 0xea147363, "printk" },
	{ 0x85f8a266, "copy_to_user" },
	{ 0xb4390f9a, "mcount" },
	{ 0xfee8a795, "mutex_lock" },
	{ 0x61651be, "strcat" },
	{ 0x9d258f, "_write_lock" },
	{ 0x7755310, "path_put" },
	{ 0x2044fa9e, "kmem_cache_alloc_trace" },
	{ 0x52683e38, "proc_create_data" },
	{ 0x37a0cba, "kfree" },
	{ 0x236c8c64, "memcpy" },
	{ 0x3302b500, "copy_from_user" },
	{ 0xe914e41e, "strcpy" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "A511FBC7EFB4697A81C70EC");

static const struct rheldata _rheldata __used
__attribute__((section(".rheldata"))) = {
	.rhel_major = 6,
	.rhel_minor = 9,
	.rhel_release = 695,
};
