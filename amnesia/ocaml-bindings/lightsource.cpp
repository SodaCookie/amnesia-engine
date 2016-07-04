#include "../classes/lightsource.h"
#include "../primitive/polygon.h"
#include "../primitive/segment.h"
#include "../primitive/vector.h"

struct std_vector {
  int size;
  void **elements;
};

extern "C" {
LightSource *create_lightsource(Vector *position, double radius, double strength) {
  return new LightSource(*position, radius, strength);
}
void lightsource_move(LightSource *light, Vector *position) { light->move(*position); }

void lightsource_process(LightSource *light, Polygon **polygons, size_t length, Polygon *view,
                         std_vector *out) {
  std::vector<Polygon> list_of_polygons = std::vector<Polygon>(length);
  for (size_t i = 0; i < length; i++) {
    list_of_polygons[i] = *(polygons[i]);
  }
  std::vector<Polygon> ret_poly = light->process(list_of_polygons, *view);
  size_t size = ret_poly.size();
  Polygon **ret_arr = (Polygon **)malloc(size * sizeof(Polygon *));
  memset(ret_arr, 0, size * sizeof(Polygon *));
  int i = 0;
  for (Polygon p : ret_poly) {
    ret_arr[i] = new Polygon(p.get_vertices());
    i++;
  }
  out->size = size;
  out->elements = (void **)ret_arr;
}
};
