#!/usr/bin/env python

import fileinput

for line in fileinput.input():
    e = line.strip().split()
    assert len(e) == 3
    addr, typ, name = e
    if typ != 'T':
        continue
    if name in ['_start', 'main']:
        continue
    if name.startswith('libs'):
        continue
    #/// print('.global\t{}'.format(name))
    # print('{}:'.format(name))
    # print('\tmovq\t$0x{}, %rax'.format(addr))
    # print('\tjmpq\t*%rax')
    # print('')

    #print('.global\t{}'.format(name))
    #print('{}:'.format(name))
    #print('\tj\t{}'.format(name))
    #print('')

    print('.global\t{}'.format(name))
    print('{}:'.format(name))
    print('\tli	a5,0x{}'.format(addr))
    print('\tjr	a5')
    #print('\taddi	a5,a5,0x{}'.format(addr))
    print('')
