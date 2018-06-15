# encoding: utf-8

import os, sys

_syscalls = [
    "sys_map_pml4",
    "sys_map_page_desc",
    "sys_map_proc",
    "sys_map_dev",
    "sys_map_file",
    "sys_alloc_pdpt",
    "sys_alloc_pd",
    "sys_alloc_pt",
    "sys_alloc_frame",
    "sys_copy_frame",
    "sys_protect_frame",
    "sys_free_pdpt",
    "sys_free_pd",
    "sys_free_pt",
    "sys_free_frame",
    "sys_reclaim_page",
    "clone_proc", # sys_clone
    "sys_set_proc_name",
    "sys_set_runnable",
    "switch_proc", # sys_switch
    "sys_kill",
    "sys_reap",
    "sys_reparent",
    "send_proc", # sys_send
    "recv_proc", # sys_recv
    "reply_wait_proc", # sys_reply_wait
    "call_proc", # sys_call
    "sys_create",
    "sys_close",
    "sys_dup",
    "sys_dup2",
    "sys_lseek",
    "sys_map_pcipage",
    "sys_alloc_iommu_root",
    "sys_alloc_iommu_pdpt",
    "sys_alloc_iommu_pd",
    "sys_alloc_iommu_pt",
    "sys_alloc_iommu_frame",
    "sys_map_iommu_frame",
    "sys_reclaim_iommu_frame",
    "sys_reclaim_iommu_root",
    "sys_alloc_vector",
    "sys_reclaim_vector",
    "sys_alloc_intremap",
    "sys_reclaim_intremap",
    "sys_ack_intr",
    "sys_alloc_io_bitmap",
    "sys_alloc_port",
    "sys_reclaim_port",
    "extintr",
]

def alltest():
    accepted = []

    for x in _syscalls:
        cmd = 'make hv6-verify -- -v --failfast HV6.test_%s'%x
        print cmd
        ret = os.system(cmd)
        accepted.append(ret)

    for i in range(len(_syscalls)):
        print _syscalls[i], accepted[i]

    count = 0
    for x in accepted:
        if x == 0:
            count += 1
    print count, '/', len(accepted)

#alltest()

def passby(filename, extra):
    accepted = []
    for line in open(filename).readlines():
        if len(line.strip()) <= 0 or line.strip().split()[1] == '/': continue

        name = line.strip().split()[0]
        x = int(line.strip().split()[1])
        if x == 0:
            accepted.append(x)
        else:
            cmd = 'make hv6-verify -- -v --failfast HV6.test_%s'%name
            print cmd
            ret = os.system(cmd)
            accepted.append(ret)
    i = 0
    for line in open(filename).readlines():
        if len(line.strip()) <= 0 or line.strip().split()[1] == '/': continue
        
        name = line.strip().split()[0]
        x = int(line.strip().split()[1])
        if x == 0:
            print line.strip()
        elif accepted[i] == 0:
            print name, 0, '->', extra
        else:
            print name, accepted[i]
        i += 1
    
    count = 0
    for x in accepted:
        if x == 0:
            count += 1
    print count, '/', len(accepted)

passby('after4.txt', 'DMAR_PTE_W')
