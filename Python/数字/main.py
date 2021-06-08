import random

print(1 << 1000)

c = 1+1j
print(c.real, c.imag, c.conjugate())

# 真正的除法，地板除
print(1 / 2, 1 // 2, 1 % 2)

# 工厂函数实现任意进制转换十进制
print(int('1000000000000', base=2))

# 进制转换函数实现十进制转换成任意进制
print(bin(4096), oct(4096), hex(4096))

print(divmod(10, 3), round(3.14156, 2))

# ASCII字符互转
print(chr(65), ord('A'))

print(random.randint(1000, 10000000))
