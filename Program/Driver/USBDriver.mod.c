#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
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
	{ 0x1deb9105, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x62aea950, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x475bfdbb, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x63a70d3e, __VMLINUX_SYMBOL_STR(usb_deregister_dev) },
	{ 0x2cf1909a, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x1b71d3ec, __VMLINUX_SYMBOL_STR(usb_register_dev) },
	{ 0x4f7aae1a, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xd2b09ce5, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x50af943, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0xf1943569, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xef551010, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x9b5bde1e, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x69ca09e3, __VMLINUX_SYMBOL_STR(usb_find_interface) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x368cc916, __VMLINUX_SYMBOL_STR(usb_bulk_msg) },
	{ 0xdf968ae4, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0xb475cb62, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0x6d0dfe2, __VMLINUX_SYMBOL_STR(usb_alloc_coherent) },
	{ 0xf2a6e0a2, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x78d9def5, __VMLINUX_SYMBOL_STR(__dynamic_dev_dbg) },
	{ 0x4d47be4a, __VMLINUX_SYMBOL_STR(usb_free_coherent) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x1e183c80, __VMLINUX_SYMBOL_STR(usb_put_dev) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v2341p0001d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "4FC67D9AE24AC8E6DE0A1EB");
