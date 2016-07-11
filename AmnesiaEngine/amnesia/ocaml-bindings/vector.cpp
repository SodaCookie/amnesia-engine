#include "../primitive/vector.h"
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>

#define Vector_val(v) Vector(Double_field(v, 0), Double_field(v, 1))

extern "C" {
CAMLprim value vector_create_vector(value double_x, value double_y) {
  CAMLparam2(double_x, double_y);
  CAMLlocal1(record_v);
  record_v = caml_alloc(2, Double_array_tag);
  Store_double_field(record_v, 0, Double_val(double_x));
  Store_double_field(record_v, 1, Double_val(double_y));
  CAMLreturn(record_v);
}
CAMLprim value vector_magnitude(value record_v) {
  CAMLparam1(record_v);
  CAMLreturn(caml_copy_double(Vector_val(record_v).magnitude()));
}
CAMLprim value vector_angle(value record_v1, value record_v2) {
  CAMLparam2(record_v1, record_v2);
  CAMLreturn(caml_copy_double(Vector_val(record_v1).angle(Vector_val(record_v2))));
}
CAMLprim value vector_set_magitude(value record_v, value double_magnitude) {
  CAMLparam2(record_v, double_magnitude);
  CAMLlocal1(record_r);
  Vector v = Vector_val(record_v);
  v.set_magnitude(Double_val(double_magnitude));
  Store_double_field(record_v, 0, v.x);
  Store_double_field(record_v, 1, v.y);
  CAMLreturn(Val_unit);
}

CAMLprim value vector_dot(value record_v1, value record_v2) {
  CAMLparam2(record_v1, record_v2);
  Vector tmp1 = Vector_val(record_v1);
  Vector tmp2 = Vector_val(record_v2);
  CAMLreturn(caml_copy_double(tmp1.dot(tmp2)));
}

CAMLprim value vector_rotate(value record_v, value double_angle) {
  CAMLparam2(record_v, double_angle);
  CAMLlocal1(record_r);
  Vector v = Vector_val(record_v).rotate(Double_val(double_angle));
  record_r = caml_alloc(2, Double_array_tag);
  Store_double_field(record_r, 0, v.x);
  Store_double_field(record_r, 1, v.y);
  CAMLreturn(record_r);
}

CAMLprim value vector_parallel(value record_v1, value record_v2) {
  CAMLparam2(record_v1, record_v2);
  CAMLreturn(Val_bool(Vector_val(record_v1).parallel(Vector_val(record_v2))));
}

CAMLprim value vector_normalized(value record_v) {
  CAMLparam1(record_v);
  CAMLlocal1(record_r);
  Vector v = Vector_val(record_v).normalized();
  record_r = caml_alloc(2, Double_array_tag);
  Store_double_field(record_r, 0, v.x);
  Store_double_field(record_r, 1, v.y);
  CAMLreturn(record_r);
}
}
