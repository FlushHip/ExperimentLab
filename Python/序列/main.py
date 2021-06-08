import string

names = ('chenyang', 'lisi', 'nidaye', 'fuck')

for i in range(len(names)):
    print('index {index} : {value}'.format(index=i, value=names[i]))

for i in range(len(names)):
    print('index {index} : {value}'.format(index=-i - 1, value=names[-i - 1]))

print(names + names, names * 2)

print(names[:], names[1:2])

print(names[::-1], names[::2])

print(names[:1] + names[2:])

alpha = string.ascii_letters + '_'
num = string.digits
print(alpha, num)

# raw string
str = r'\n'
print(str)
str = u'陈阳'
print(str)

three_str ='''{
    'name' : 'flushhip',
    'ids' : [
        1,
        2,
        5
    ]
}
'''
print(three_str)

names = list(names)
print(names)
