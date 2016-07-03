#include "../primitive/segment.cpp"
#include "../primitive/vector.cpp"

std::pair<bool, Vector *> *to_heap_ptr(std::pair<bool, Vector> v) {
  Vector *v2 = nullptr;
  if (v.first) {
    v2 = new Vector(v.second.x, v.second.y);
  }
  return new std::pair<bool, Vector *>(v.first, v2);
}

extern "C" {
Segment *create_segment(Vector *anchor, Vector *direction) {
  return new Segment(*anchor, *direction);
}
void destroy_segment(Segment *s) { delete s; }

std::pair<bool, Vector *> *intersect_segment(Segment *first, Segment *second) {
  return to_heap_ptr(first->intersect_segment(*second));
}

std::pair<bool, Vector *> *intersect_ray(Segment *first, Segment *second) {
  return to_heap_ptr(first->intersect_ray(*second));
}

std::pair<bool, Vector *> *intersect_line(Segment *first, Segment *second) {
  return to_heap_ptr(first->intersect_line(*second));
}
}