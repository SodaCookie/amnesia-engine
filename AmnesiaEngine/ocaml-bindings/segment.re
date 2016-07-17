
type segmentT = {anchor: Vector.vectorT, direction: Vector.vectorT};

external create_segment : Vector.vectorT => Vector.vectorT => segmentT = "segment_create_segment";

external intersect_segment : segmentT => segmentT => option Vector.vectorT = "segment_intersect_segment";

external intersect_ray : segmentT => segmentT => option Vector.vectorT = "segment_intersect_ray";

external intersect_line : segmentT => segmentT => option Vector.vectorT = "segment_intersect_line";

let to_string p =>
  "{anchor: " ^ Vector.to_string p.anchor ^ ", direction: " ^ Vector.to_string p.direction ^ "}";
