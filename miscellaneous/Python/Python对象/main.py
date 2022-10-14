x = 1
y = 1 + 1
print(id(x), type(x), type(type(x)))
print(x is y, id(x) == id(y))

# 可变类型：列表、字典。变动时不改变内存地址，只改变内存地址上的值。
