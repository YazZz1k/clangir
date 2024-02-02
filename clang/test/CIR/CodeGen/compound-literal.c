// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -fclangir-enable -emit-cir %s -o %t.cir
// RUN: FileCheck --input-file=%t.cir %s

typedef struct {
  int *arr;
} S;

S a = {
  .arr = (int[]){}
};
// CHECK: cir.global "private" internal @".compoundLiteral.0" = #cir.zero : !cir.array<!s32i x 0> {alignment = 4 : i64}
// CHECK: cir.global external @a = #cir.const_struct<{#cir.global_view<@".compoundLiteral.0"> : !cir.ptr<!s32i>}> : !ty_22S22

S b = {
  .arr = (int[]){1}
};
// CHECK: cir.global "private" internal @".compoundLiteral.1" = #cir.const_array<[#cir.int<1> : !s32i]> : !cir.array<!s32i x 1> {alignment = 4 : i64}
// CHECK: cir.global external @b = #cir.const_struct<{#cir.global_view<@".compoundLiteral.1"> : !cir.ptr<!s32i>}> : !ty_22S22
