#include "../primitive/segment.h"
#include "../primitive/vector.h"
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>

#define Segment_val(v)                                                                             \
  Segment(Vector(Double_field(Field(v, 0), 0), Double_field(Field(v, 0), 1)),                      \
          Vector(Double_field(Field(v, 1), 0), Double_field(Field(v, 1), 1)))
// Ripped from ctypes
#define Val_none Val_int(0)
#define Some_val(v) Field(v, 0)

static value Val_some(value v) {
  CAMLparam1(v);
  CAMLlocal1(some);
  some = caml_alloc_small(1, 0);
  Field(some, 0) = v;
  CAMLreturn(some);
}

extern "C" {
CAMLprim value segment_create_segment(value vector_anchor, value vector_direction) {
  CAMLparam2(vector_anchor, vector_direction);
  CAMLlocal1(record_segment);
  record_segment = caml_alloc_small(2, 0);
  Field(record_segment, 0) = vector_anchor;
  Field(record_segment, 1) = vector_direction;
  CAMLreturn(record_segment);
}
CAMLprim value segment_intersect_segment(value segment1, value segment2) {
  CAMLparam2(segment1, segment2);
  CAMLlocal1(record_vector);
  Segment s = Segment_val(segment1);
  Segment s2 = Segment_val(segment2);
  Vector out;
  if (s.intersect_segment(s2, out)) {
    record_vector = caml_alloc_small(2, Double_array_tag);
    Double_field(record_vector, 0) = out.x;
    Double_field(record_vector, 1) = out.y;
    CAMLreturn(Val_some(record_vector));
  } else {
    CAMLreturn(Val_none);
  }
}
CAMLprim value segment_intersect_ray(value segment1, value segment2) {
  CAMLparam2(segment1, segment2);
  CAMLlocal1(record_vector);
  Segment s = Segment_val(segment1);
  Segment s2 = Segment_val(segment2);
  Vector out;
  if (s.intersect_ray(s2, out)) {
    record_vector = caml_alloc_small(2, Double_array_tag);
    Double_field(record_vector, 0) = out.x;
    Double_field(record_vector, 1) = out.y;
    CAMLreturn(Val_some(record_vector));
  } else {
    CAMLreturn(Val_none);
  }
}
CAMLprim value segment_intersect_line(value segment1, value segment2) {
  CAMLparam2(segment1, segment2);
  CAMLlocal1(record_vector);
  Segment s = Segment_val(segment1);
  Segment s2 = Segment_val(segment2);
  Vector out;
  if (s.intersect_line(s2, out)) {
    record_vector = caml_alloc_small(2, Double_array_tag);
    Double_field(record_vector, 0) = out.x;
    Double_field(record_vector, 1) = out.y;
    CAMLreturn(Val_some(record_vector));
  } else {
    CAMLreturn(Val_none);
  }
}
}
