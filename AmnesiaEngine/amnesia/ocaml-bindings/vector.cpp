#include "../primitive/vector.h"
#include <iostream>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>

void addch(int x) {
  std::cout << "heyo " << x << std::endl;
}

Vector *to_heap_ptr(Vector v) { return new Vector(v.x, v.y); }

extern "C" {
  CAMLprim value caml_curses_addch(value c) {
    CAMLparam1 (c);
    addch(Int_val(c));            /* Characters are encoded like integers */
    CAMLreturn (Val_unit);
  }
Vector *create_vector(double x, double y) { return new Vector(x, y); }
void destroy_vector(Vector *s) { delete s; }
double vector_magnitude(Vector *v) { return v->magnitude(); }

double vector_angle(Vector *v1, Vector *v2) { return v1->angle(*v2); }

void vector_set_magitude(Vector *v, double magnitude) { v->set_magnitude(magnitude); }

double vector_dot(Vector *v1, Vector *v2) { return v1->dot(*v2); }

Vector *vector_rotate(Vector *v, double angle) { return to_heap_ptr(v->rotate(angle)); }

bool vector_parallel(Vector *v1, Vector *v2) { return v1->parallel(*v2); }

Vector *vector_normalized(Vector *v) { return to_heap_ptr(v->normalized()); }

//============== Operators =============//
Vector *vector_add(Vector *left, Vector *right) { return to_heap_ptr(*left + *right); }

Vector *vector_subtract(Vector *left, Vector *right) { return to_heap_ptr(*left - *right); }

Vector *vector_multiply(Vector *left, double constant) { return to_heap_ptr(*left * constant); }

Vector *vector_divide(Vector *left, double constant) { return to_heap_ptr(*left / constant); }

Vector *vector_opposite(Vector *v) { return to_heap_ptr(-*v); }

double vector_get_x(Vector *v) { return v->x; }

double vector_get_y(Vector *v) { return v->y; }
}
