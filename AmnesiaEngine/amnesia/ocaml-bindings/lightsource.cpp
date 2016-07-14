#include "../classes/lightsource.h"
#include "../primitive/polygon.h"
#include "../primitive/segment.h"
#include "../primitive/vector.h"
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>
#include <vector>
#include <cstdio>
#include <chrono>

#define Vector_val(v) Vector(Double_field(v, 0), Double_field(v, 1))

static void vector_list_to_std_vector(value list, std::vector<Vector> *out) {
  // End of list
  if (Int_val(list) == 0) {
    return;
  }
  out->push_back(Vector_val(Field(list, 0)));
  vector_list_to_std_vector(Field(list, 1), out);
}

static void polygon_list_to_std_vector(value list, std::vector<Polygon> *out) {
  // End of list
  if (Int_val(list) == 0) {
    return;
  }
  std::vector<Vector> vertices = std::vector<Vector>();
  vector_list_to_std_vector(Field(Field(list, 0), 0), &vertices);
  out->push_back(Polygon(vertices));
  polygon_list_to_std_vector(Field(list, 1), out);
}

extern "C" {
CAMLprim value lightsource_create_lightsource(value vector_position, value double_radius,
                                              value double_strength) {
  CAMLparam3(vector_position, double_radius, double_strength);
  CAMLlocal1(record_lightsource);
  record_lightsource = caml_alloc_small(3, 0);
  Field(record_lightsource, 0) = vector_position;
  Field(record_lightsource, 1) = double_radius;
  Field(record_lightsource, 2) = double_strength;
  CAMLreturn(record_lightsource);
}

CAMLprim value lightsource_move_lightsource(value lightsource, value vector_position) {
  CAMLparam2(lightsource, vector_position);
  Field(lightsource, 0) = vector_position;
  CAMLreturn(Val_unit);
}

CAMLprim value lightsource_process(value record_lightsource, value list_polygon_objects,
                                   value polygon_view) {
  CAMLparam3(record_lightsource, list_polygon_objects, polygon_view);
  CAMLlocal5(polygon_prev_head, list_polygon_head, vector_prev_head, list_vector_head, tmp_polygon);
  CAMLlocal1(tmp_vector);
  LightSource l = LightSource(Vector_val(Field(record_lightsource, 0)),
                              Double_val(Field(record_lightsource, 1)),
                              Double_val(Field(record_lightsource, 2)));
  std::vector<Polygon> tmp_polygon_list = std::vector<Polygon>();
  polygon_list_to_std_vector(list_polygon_objects, &tmp_polygon_list);
  std::vector<Vector> tmp_vector_list = std::vector<Vector>();
  vector_list_to_std_vector(Field(polygon_view, 0), &tmp_vector_list);
  Polygon polygon = Polygon(tmp_vector_list);
  auto start = std::chrono::steady_clock::now();
  std::vector<Polygon> list_polygon = l.process(tmp_polygon_list, polygon);
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                            (std::chrono::steady_clock::now() - start);
  printf("--> %lld\n", duration.count());
  polygon_prev_head = Val_unit;
  for (Polygon p : list_polygon) {
    vector_prev_head = Val_unit;
    for (Vector v : p.get_vertices()) {
      tmp_vector = caml_alloc_small(2, Double_array_tag);
      Double_field(tmp_vector, 0) = v.x;
      Double_field(tmp_vector, 1) = v.y;
      list_vector_head = caml_alloc_small(2, 0);
      Field(list_vector_head, 0) = tmp_vector;
      Field(list_vector_head, 1) = vector_prev_head;
      vector_prev_head = list_vector_head;
    }
    tmp_polygon = caml_alloc_small(1, 0);
    Field(tmp_polygon, 0) = list_vector_head;

    list_polygon_head = caml_alloc_small(2, 0);
    Field(list_polygon_head, 0) = tmp_polygon;
    Field(list_polygon_head, 1) = polygon_prev_head;
    polygon_prev_head = list_polygon_head;
  }
  CAMLreturn(list_polygon_head);
}
};
