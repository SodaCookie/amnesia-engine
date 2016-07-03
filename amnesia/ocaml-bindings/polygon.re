
open Ctypes;

open Foreign;

type polygonT;

let polygonT: typ (structure polygonT) = structure "Polygon";

type std_vectorT;

let std_vector: typ (structure std_vectorT) = structure "std_vector";

let vec_size_helper = field std_vector "size" int;

let vec_size v => getf v vec_size_helper;

let elements_helper = field std_vector "elements" (ptr void);

let elements t v => from_voidp t (getf v elements_helper);

seal std_vector;

let create_polygon_helper =
  foreign
    "polygon_create_polygon" (ptr (ptr Vector.vectorT) @-> size_t @-> returning (ptr polygonT));

let create_polygon arr => {
  let open Unsigned.Size_t;
  let arr = CArray.of_list (ptr Vector.vectorT) arr;
  let len = of_int (CArray.length arr);
  let start = CArray.start arr;
  create_polygon_helper start len
};

let get_vertices_helper =
  foreign "polygon_get_vertices" (ptr polygonT @-> ptr std_vector @-> returning void);

let get_vertices poly => {
  let v = make std_vector;
  get_vertices_helper poly (addr v);
  let ret = CArray.from_ptr (elements (ptr Vector.vectorT) v) (vec_size v);
  ret
};

let get_sides_helper =
  foreign "polygon_get_sides" (ptr polygonT @-> ptr std_vector @-> returning void);

let get_sides poly => {
  let v = make std_vector;
  get_sides_helper poly (addr v);
  let ret = CArray.from_ptr (elements (ptr Segment.segmentT) v) (vec_size v);
  ret
};

let vertices_to_string a => {
  let bla = CArray.to_list a;
  switch bla {
  | [] => ""
  | [el] => Vector.to_string el
  | [el, ...rest] =>
    "[" ^
      Vector.to_string el ^
      List.fold_left (fun acc cur => acc ^ ", " ^ Vector.to_string cur) "" rest ^
      "]"
  }
};

let segments_to_string a => {
  let bla = CArray.to_list a;
  switch bla {
  | [] => ""
  | [el] => Segment.to_string el
  | [el, ...rest] =>
    "[" ^
      Segment.to_string el ^
      List.fold_left (fun acc cur => acc ^ ", " ^ Segment.to_string cur) "" rest ^
      "]"
  }
};

let list_to_string a => {
  let bla = Ctypes.CArray.to_list a;
  switch bla {
  | [] => ""
  | [el] => vertices_to_string (get_vertices el)
  | [el, ...rest] =>
    "[" ^
      vertices_to_string (get_vertices el) ^
      List.fold_left (fun acc cur => acc ^ ", " ^ vertices_to_string (get_vertices cur)) "" rest ^
      "]"
  }
};
