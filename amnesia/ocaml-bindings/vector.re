
open Ctypes;

open Foreign;

type vectorT;

let vectorT: typ (structure vectorT) = structure "Vector";

let create_vector = foreign "create_vector" (double @-> double @-> returning (ptr vectorT));

let destroy_vector = foreign "destroy_vector" (ptr vectorT @-> returning void);

let magnitude = foreign "vector_magnitude" (ptr vectorT @-> returning double);

let add = foreign "vector_add" (ptr vectorT @-> ptr vectorT @-> returning (ptr vectorT));

let get_x = foreign "vector_get_x" (ptr vectorT @-> returning double);

let get_y = foreign "vector_get_y" (ptr vectorT @-> returning double);

let to_string v => "(" ^ (string_of_float @@ get_x v) ^ ", " ^ (string_of_float @@ get_y v) ^ ")";

let angle = foreign "vector_angle" (ptr vectorT @-> ptr vectorT @-> returning double);

let set_magitude = foreign "vector_set_magitude" (ptr vectorT @-> double @-> returning void);

let dot = foreign "vector_dot" (ptr vectorT @-> ptr vectorT @-> returning double);

let rotate = foreign "vector_rotate" (ptr vectorT @-> ptr vectorT @-> returning (ptr vectorT));

let parallel = foreign "vector_parallel" (ptr vectorT @-> ptr vectorT @-> returning bool);

let normalized =
  foreign "vector_normalized" (ptr vectorT @-> ptr vectorT @-> returning (ptr vectorT));

let (+->) = foreign "vector_add" (ptr vectorT @-> ptr vectorT @-> returning (ptr vectorT));

let (-->) = foreign "vector_subtract" (ptr vectorT @-> ptr vectorT @-> returning (ptr vectorT));

let (*->) = fun a b => a + b;
let (\->) = foreign "vector_divide" (ptr vectorT @-> double @-> returning (ptr vectorT));
