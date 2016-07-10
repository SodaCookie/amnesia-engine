/*
open Ctypes;

open Foreign;

type segmentT;

let segmentT: typ (structure segmentT) = structure "Segment";

let create_segment_helper =
  foreign "create_segment" (ptr Vector.vectorT @-> ptr Vector.vectorT @-> returning (ptr segmentT));

let create_segment anchor::anchor direction::direction => create_segment_helper anchor direction;

let destroy_segment = foreign "destroy_segment" (ptr segmentT @-> returning void);

let get_anchor = foreign "segment_get_anchor" (ptr segmentT @-> returning (ptr Vector.vectorT));

let get_direction = foreign "segment_get_direction" (ptr segmentT @-> returning (ptr Vector.vectorT));

let intersect_segment a b => Maybe.wrap (
  (foreign "segment_intersect_segment" (ptr segmentT @-> ptr segmentT @-> returning (ptr Maybe.maybeT)))
    a b
);

let intersect_ray a b => Maybe.wrap (
  (foreign "segment_intersect_ray" (ptr segmentT @-> ptr segmentT @-> returning (ptr Maybe.maybeT))) a b
);

let intersect_line a b => Maybe.wrap (
  (foreign "segment_intersect_line" (ptr segmentT @-> ptr segmentT @-> returning (ptr Maybe.maybeT))) a b
);

let to_string s => "{\n  anchor: " ^ (Vector.to_string (get_anchor s)) ^ ",\n  direction: " ^ (Vector.to_string (get_direction s)) ^"\n}"; */
