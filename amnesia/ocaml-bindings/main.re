
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
| Some v => print_endline @@ to_string v
};

let bl = create_vector 100. 100.;

let tl = create_vector 100. 200.;

let tr = create_vector 200. 200.;

let br = create_vector 200. 100.;

let poly1 = Polygon.create_polygon [bl, tl, tr, br];

let arr = Polygon.get_vertices poly1;

print_endline @@ Polygon.vertices_to_string arr;

let arr2 = Polygon.get_sides poly1;

print_endline @@ Polygon.segments_to_string arr2;

let light = Lightsource.create_lightsource (create_vector 320. 240.) 200. 1.;

let bl2 = create_vector 0. 0.;

let tl2 = create_vector 0. 480.;

let tr2 = create_vector 640. 480.;

let br2 = create_vector 640. 0.;

let view = Polygon.create_polygon [bl2, tl2, tr2, br2];

let polygon_list = Lightsource.process lightsource::light objects::[poly1] view::view;

print_endline @@ Polygon.list_to_string polygon_list;
