#include "../primitive/polygon.cpp"
#include "../primitive/segment.cpp"
#include "../primitive/vector.cpp"

struct std_vector {
  int size;
  void **elements;
};

extern "C" {
Polygon *polygon_create_polygon(Vector **vertices, size_t length) {
  std::vector<Vector> list_of_vertices = std::vector<Vector>(length);
  for (size_t i = 0; i < length; i++) {
    list_of_vertices[i] = *(vertices[i]);
  }
  return new Polygon(list_of_vertices);
}

void polygon_get_vertices(Polygon *polygon, std_vector *out) {
  std::vector<Vector> vertices = polygon->get_vertices();
  int64_t size = vertices.size();

  Vector **ret_arr = (Vector **)malloc(size * sizeof(Vector *));
  memset(ret_arr, 0, size * sizeof(Vector *));
  int i = 0;
  for (Vector v : vertices) {
    ret_arr[i] = new Vector(v.x, v.y);
    i++;
  }
  out->size = size;
  out->elements = (void **)ret_arr;
}

void polygon_get_sides(Polygon *polygon, std_vector *out) {
  std::vector<Segment> sides = polygon->get_sides();
  int64_t size = sides.size();

  Segment **ret_arr = (Segment **)malloc(size * sizeof(Segment *));
  memset(ret_arr, 0, size * sizeof(Segment *));
  int i = 0;
  for (Segment s : sides) {
    ret_arr[i] = new Segment(s.anchor, s.direction);
    i++;
  }
  out->size = size;
  out->elements = (void **)ret_arr;
}
}
