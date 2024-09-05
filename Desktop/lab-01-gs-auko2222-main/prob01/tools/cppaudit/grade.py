
from gggg import *

a = Assignment(10, 4)
s = State(a)

horizontal_rule()

s.reject_if_file_unchanged('main.cc',
                           'd38cb7f82528d14ef3ee4bd087bcaa76d075f57506a8da93f4a7284a2b36c9c3')

s.reject_if_file_changed('tools/settings/unittest.cc',
                         'e12440792454f76c6df008d828be66bbe118b9020e7aac6a78a8a00956ab9d50')

s.gtest_run('tools/output/unittest')
s.gtest_suite_test('UserInput', 3)
s.gtest_suite_test('Taxes', 3)
s.gtest_suite_test('Tip', 4)

s.summarize()