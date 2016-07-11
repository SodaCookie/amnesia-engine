#include "../primitive/vector.h"
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>

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
  CAMLreturn(
      caml_copy_double(Vector(Double_field(record_v, 0), Double_field(record_v, 1)).magnitude()));
}
CAMLprim value vector_angle(value record_v, value record_v2) {
  CAMLparam2(record_v, record_v2);
  CAMLreturn(
      caml_copy_double(Vector(Double_field(record_v, 0), Double_field(record_v, 1))
                           .angle(Vector(Double_field(record_v2, 0), Double_field(record_v2, 1)))));
}
CAMLprim value vector_set_magitude(value record_v, value double_magnitude) {
  CAMLparam2(record_v, double_magnitude);
  CAMLlocal1(record_r);
  Vector v = Vector(Double_field(record_v, 0), Double_field(record_v, 1));
  v.set_magnitude(Double_val(double_magnitude));
  record_r = caml_alloc(2, Double_array_tag);
  Store_double_field(record_r, 0, v.x);
  Store_double_field(record_r, 1, v.y);
  CAMLreturn(record_r);
}

CAMLprim value vector_dot(value record_v1, value record_v2) {
  CAMLparam2(record_v1, record_v2);
  Vector tmp1 = Vector(Double_field(record_v1, 0), Double_field(record_v1, 1));
  Vector tmp2 = Vector(Double_field(record_v2, 0), Double_field(record_v2, 1));
  CAMLreturn(caml_copy_double(tmp1.dot(tmp2)));
}

CAMLprim value vector_rotate(value record_v, value double_angle) {
  CAMLparam2(record_v, double_angle);
  CAMLlocal1(record_r);
  Vector v =
      Vector(Double_field(record_v, 0), Double_field(record_v, 1)).rotate(Double_val(double_angle));
  record_r = caml_alloc(2, Double_array_tag);
  Store_double_field(record_r, 0, v.x);
  Store_double_field(record_r, 1, v.y);
  CAMLreturn(record_r);
}

CAMLprim value vector_parallel(value record_v1, value record_v2) {
  CAMLparam2(record_v1, record_v2);
  CAMLreturn(
      Val_bool(Vector(Double_field(record_v1, 0), Double_field(record_v1, 1))
                   .parallel(Vector(Double_field(record_v2, 0), Double_field(record_v2, 1)))));
}

CAMLprim value vector_normalized(value record_v) {
  CAMLparam1(record_v);
  CAMLlocal1(record_r);
  Vector v = Vector(Double_field(record_v, 0), Double_field(record_v, 1)).normalized();
  record_r = caml_alloc(2, Double_array_tag);
  Store_double_field(record_r, 0, v.x);
  Store_double_field(record_r, 1, v.y);
  CAMLreturn(record_r);
}
}
