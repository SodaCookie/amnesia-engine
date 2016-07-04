
open Ctypes;

open Foreign;

type std_vectorT;

let std_vector: typ (structure std_vectorT) = structure "std_vector";

let vec_size_helper = field std_vector "size" int;

let vec_size v => getf v vec_size_helper;

let elements_helper = field std_vector "elements" (ptr void);

let elements t v => from_voidp t (getf v elements_helper);

seal std_vector;

type lightsourceT;

let lightsourceT: typ (structure lightsourceT) = structure "LightSource";

let create_lightsource =
  foreign
    "create_lightsource"
    (ptr Vector.vectorT @-> double @-> double @-> returning (ptr lightsourceT));

let process_helper =
  foreign
    "lightsource_process"
    (
      ptr lightsourceT @->
        ptr (ptr Polygon.polygonT) @->
        size_t @->
        ptr Polygon.polygonT @->
        ptr std_vector @->
        returning void
    );

let process lightsource::lightsource objects::objects view::view => {
  let open Unsigned.Size_t;
  let arr = CArray.of_list (ptr Polygon.polygonT) objects;
  let len = of_int (CArray.length arr);
  let start = CArray.start arr;
  let poly = make std_vector;
  process_helper lightsource start len view (addr poly);
  let ret = CArray.from_ptr (elements (ptr Polygon.polygonT) poly) (vec_size poly);
  ret
}
