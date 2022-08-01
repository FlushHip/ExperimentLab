#pragma once

namespace lib_static {
namespace a {

extern int global_i;
int& static_var();
int& global_var();
void print();
}  // namespace a
}  // namespace lib_static
