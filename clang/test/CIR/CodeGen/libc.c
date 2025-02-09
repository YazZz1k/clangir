// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -fclangir-enable -emit-cir %s -o %t.cir
// RUN: FileCheck --input-file=%t.cir %s

// Should generate CIR's builtin memcpy op.
void *memcpy(void *, const void *, unsigned long);
void testMemcpy(void *src, const void *dst, unsigned long size) {
  memcpy(dst, src, size);
  // CHECK: cir.libc.memcpy %{{.+}} bytes from %{{.+}} to %{{.+}} : !u64i, !cir.ptr<!void> -> !cir.ptr<!void>
}

double fabs(double);
double testFabs(double x) {
  return fabs(x);
  // CHECK: cir.fabs %{{.+}} : f64
}

float fabsf(float);
float testFabsf(float x) {
  return fabsf(x);
  // CHECK: cir.fabs %{{.+}} : f32
}
