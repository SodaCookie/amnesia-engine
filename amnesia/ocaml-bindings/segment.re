
open Ctypes;

open Foreign;

type segmentT;

let segmentT: typ (structure segmentT) = structure "Segment";

let create_segment =
  foreign "create_segment" (ptr Vector.vectorT @-> ptr Vector.vectorT @-> returning (ptr segmentT));

let create_segment anchor::anchor direction::direction => create_segment anchor direction;

let destroy_segment = foreign "destroy_segment" (ptr segmentT @-> returning void);

let intersect_segment a b =>
  Maybe.wrap ((foreign "intersect_segment" (ptr segmentT @-> ptr segmentT @-> returning (ptr Maybe.maybeT))) a b);

let intersect_ray a b =>
  Maybe.wrap ((foreign "intersect_ray" (ptr segmentT @-> ptr segmentT @-> returning (ptr Maybe.maybeT))) a b);

let intersect_line a b =>
  Maybe.wrap ((foreign "intersect_line" (ptr segmentT @-> ptr segmentT @-> returning (ptr Maybe.maybeT))) a b);
