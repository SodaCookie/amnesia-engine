#include "../amnesia/primitive/polygon.h"
#include "../amnesia/primitive/segment.h"
#include "../amnesia/primitive/vector.h"
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>

extern "C" {
CAMLprim value polygon_create_polygon(value vertices_list) {
  CAMLparam1(vertices_list);
  CAMLlocal1(record_polygon_ret);
  record_polygon_ret = caml_alloc_small(1, 0);
  Field(record_polygon_ret, 0) = vertices_list;
  CAMLreturn(record_polygon_ret);
}
}
