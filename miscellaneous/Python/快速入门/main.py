import decimal, json

print('Hello Python')

print(2 ** 100)

print(True and False or True and not True)

print(decimal.Decimal('10.01'))

str_a = 'str_a'
str_b = 'str_b'
print(str_a + str_b, str_a * 2 + '#' + str_b * 2)
print(str_a[0], str_a[-1])
print(str_a[:1], str_a[1:])

array_a = [1, 'a', 2.5]
tuple_a = ((1, 2), 3, array_a)
print(array_a)
print(tuple_a)

map_a = {
    1 : array_a,
    2 : tuple_a
}
print(map_a)
print(json.dumps(map_a, indent=2, separators=(',', ':')))

if True:
    print(True)
else:
    print(False)

for i in range(len('abc')):
    print(i)
for i, c in enumerate('abc'):
    print(i, c)

# 列表解析
squared = [x ** 2 for x in range(4)]
for item in squared:
    print(item)

class CA(object):
    name = 'flushhip'

    def __init__(self):
        print(__name__)

    def get_name(self):
        return self.name

    def moc(self):
        return self.__class__.__base__.__name__

ca = CA()
print(ca.get_name(), ca.moc(), str(ca), dir(ca), help(ca), type(ca))
