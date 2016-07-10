
type vectorT = {x: float, y: float};

external create_vector : float => float => vectorT = "vector_create_vector";

external magnitude : vectorT => float = "vector_magnitude";

external angle : vectorT => vectorT => float = "vector_angle";

external set_magitude : vectorT => float => vectorT = "vector_set_magitude";

external dot : vectorT => vectorT => float = "vector_dot";

external rotate : vectorT => float => vectorT = "vector_rotate";

external parallel : vectorT => vectorT => bool = "vector_parallel";

external normalized : vectorT => vectorT = "vector_normalized";

let (+) v1 v2 => create_vector (v1.x +. v2.x) (v1.y +. v2.y);

let (-) v1 v2 => create_vector (v1.x -. v2.x) (v1.y -. v2.y);

let ( * ) v1 d => create_vector (v1.x *. d) (v1.y *. d);

let ( * ) v1 d => create_vector (v1.x /. d) (v1.y /. d);

let to_string v => "{x: " ^ string_of_float v.x ^ ", y: " ^ string_of_float v.y ^ "}";
