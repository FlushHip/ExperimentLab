import logging
import pdb
import cProfile

logging.basicConfig(level=logging.DEBUG)

# comment

print('a'
    'b');print('a'\
    'b');print('''ni
      ce''')

x = y = z = 1
a, b = 2, 3
print(x, y, z, a, b)
a, b = b, a
print(a, b)

class CA:
    # private
    _name = 'flushhip'

    # private
    def _get_name(self):
        return self._name

    def name(self):
        return self._get_name()

print(CA()._get_name(), CA().name(), CA()._name)

logging.info('logging ...')

pdb.set_trace()
