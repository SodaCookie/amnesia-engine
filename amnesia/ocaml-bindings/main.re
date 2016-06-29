
open Vector;

let a = create_vector 10. 10.;

let b = (create_vector 1. 1. +-> create_vector 2. 2.) --> create_vector 1. 1.;

let seg = Segment.create_segment anchor::a direction::b;

let a2 = create_vector 12. 10.;

let b2 = create_vector (-2.) 2.;

let seg2 = Segment.create_segment anchor::a2 direction::b2;

let intersect = Segment.intersect_segment seg seg2;

switch intersect {
| None => print_endline ":((("
| Some v =>
  print_endline @@ (
    "(" ^ (string_of_float @@ vector_get_x v) ^ ", " ^ (string_of_float @@ vector_get_y v) ^ ")"
  )
};
